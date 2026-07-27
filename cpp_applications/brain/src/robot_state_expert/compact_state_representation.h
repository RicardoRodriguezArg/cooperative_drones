#ifndef BUTLER_ROBOT_STATE_STATE_H
#define BUTLER_ROBOT_STATE_STATE_H

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>

#include "../definitions.h"
#include "../utils/concepts/validators.h"

namespace butler::robot_state {

// ─── CompactComponentStateRepresentation ──────────────────────────────────────
//
// Stores one state value per component in a packed bitfield.
//
// Layout (kBitsPerState = 2 as example):
//   word 0: [comp0][comp1][comp2]...[comp31]
//   word 1: [comp32]...
//
// Position for component C (enum underlying value = slot):
//   bit_start = slot × kBitsPerState
//   word      = bit_start / 64
//   offset    = bit_start % 64
//
// Read : (data_[word] >> offset) & kMask
// Write: data_[word] = (data_[word] & ~(kMask << offset)) | (value << offset)
// Cross-word writes/reads are handled when offset + kBitsPerState > 64.

template<butler::concepts::SentinelEnum TComponent,
         butler::concepts::SentinelEnum TState>
struct CompactComponentStateRepresentation {

    static constexpr std::size_t kComponentCount =
        static_cast<std::size_t>(TComponent::_Count);

    static constexpr std::size_t kStateCount =
        static_cast<std::size_t>(TState::_Count);

    // Minimum bits to represent every TState value (e.g. 3 states → 2 bits)
    static constexpr std::size_t kBitsPerState =
        std::bit_width(kStateCount - 1u);

    static constexpr std::size_t kTotalBits = kComponentCount * kBitsPerState;
    static constexpr std::size_t kWords     = (kTotalBits + 63) / 64;

    static constexpr std::uint64_t kMask =
        (kBitsPerState < 64) ? ((std::uint64_t{1} << kBitsPerState) - 1)
                             : ~std::uint64_t{0};

    static_assert(kComponentCount  > 0, "component enum must have at least one value before _Count");
    static_assert(kStateCount      > 1, "state enum must have at least two values before _Count");
    static_assert(kBitsPerState   <= 64, "too many state values to pack into 64-bit words");

    // All components start at TState value 0 (e.g. Unknown) — evaluated at compile time
    consteval CompactComponentStateRepresentation() noexcept
        : CompactComponentStateRepresentation(static_cast<TState>(0)) {}

    consteval explicit CompactComponentStateRepresentation(TState initial) noexcept
        : data_{} {
        for (std::size_t i = 0; i < kComponentCount; ++i)
            write(i, initial);
    }

    [[nodiscard]] constexpr TState get(TComponent component) const noexcept {
        return read(static_cast<std::size_t>(component));
    }

    constexpr void set(TComponent component, TState state) noexcept {
        write(static_cast<std::size_t>(component), state);
    }

    [[nodiscard]] static constexpr std::size_t component_count() noexcept { return kComponentCount; }
    [[nodiscard]] static constexpr std::size_t bits_per_state()  noexcept { return kBitsPerState;  }
    [[nodiscard]] static constexpr std::size_t word_count()      noexcept { return kWords;         }

private:
    [[nodiscard]] constexpr TState read(std::size_t slot) const noexcept {
        const std::size_t bit    = slot * kBitsPerState;
        const std::size_t word   = bit / 64;
        const std::size_t offset = bit % 64;

        if (offset + kBitsPerState <= 64) {
            return static_cast<TState>((data_[word] >> offset) & kMask);
        }

        // Cross-word: low bits from word, high bits from word+1
        const std::size_t   lo_bits = 64 - offset;
        const std::uint64_t lo_val  = data_[word] >> offset;
        const std::size_t   hi_bits = kBitsPerState - lo_bits;
        const std::uint64_t hi_mask = (std::uint64_t{1} << hi_bits) - 1;
        const std::uint64_t hi_val  = data_[word + 1] & hi_mask;
        return static_cast<TState>(lo_val | (hi_val << lo_bits));
    }

    constexpr void write(std::size_t slot, TState state) noexcept {
        const std::size_t   bit    = slot * kBitsPerState;
        const std::size_t   word   = bit / 64;
        const std::size_t   offset = bit % 64;
        const std::uint64_t value  = static_cast<std::uint64_t>(state) & kMask;

        if (offset + kBitsPerState <= 64) {
            data_[word] = (data_[word] & ~(kMask << offset)) | (value << offset);
            return;
        }

        // Cross-word: write low bits to word, high bits to word+1
        const std::size_t   lo_bits = 64 - offset;
        const std::uint64_t lo_mask = (std::uint64_t{1} << lo_bits) - 1;
        data_[word] = (data_[word] & ~(lo_mask << offset)) | ((value & lo_mask) << offset);

        const std::size_t   hi_bits = kBitsPerState - lo_bits;
        const std::uint64_t hi_mask = (std::uint64_t{1} << hi_bits) - 1;
        data_[word + 1] = (data_[word + 1] & ~hi_mask) | (value >> lo_bits);
    }

    std::array<std::uint64_t, kWords> data_;
};

} // namespace butler::robot_state

#endif // BUTLER_ROBOT_STATE_STATE_H
