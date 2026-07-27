#ifndef BUTLER_UTILS_PARSERS_XML_PARSER_H
#define BUTLER_UTILS_PARSERS_XML_PARSER_H

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

#include <tinyxml2.h>

namespace butler::utils::parsers {

class XmlParser {
public:
    explicit XmlParser(std::filesystem::path path)
        : m_path(std::move(path)) {
        validate_path();
        load_document();
    }

    [[nodiscard]] const std::filesystem::path& path() const noexcept {
        return m_path;
    }

    [[nodiscard]] std::string get_string(std::initializer_list<std::string_view> element_path) const {
        const tinyxml2::XMLElement& node = element(element_path);
        const char* text = node.GetText();
        if (text == nullptr) {
            throw std::runtime_error("Missing text value in XML element: " + join_path(element_path));
        }

        return trim(std::string(text));
    }

    [[nodiscard]] std::size_t get_size_t(std::initializer_list<std::string_view> element_path) const {
        const std::string value = get_string(element_path);
        if (value.empty() || value.front() == '-') {
            throw std::runtime_error("Invalid unsigned integer in XML element " + join_path(element_path)
                                     + ": " + value);
        }

        std::size_t parsed_chars = 0;
        unsigned long long parsed = 0;
        try {
            parsed = std::stoull(value, &parsed_chars);
        } catch (const std::exception&) {
            throw std::runtime_error("Invalid unsigned integer in XML element " + join_path(element_path)
                                     + ": " + value);
        }

        if (parsed_chars != value.size() || parsed > std::numeric_limits<std::size_t>::max()) {
            throw std::runtime_error("Invalid unsigned integer in XML element " + join_path(element_path)
                                     + ": " + value);
        }

        return static_cast<std::size_t>(parsed);
    }

    [[nodiscard]] bool get_bool(std::initializer_list<std::string_view> element_path) const {
        std::string value = get_string(element_path);
        std::transform(value.begin(), value.end(), value.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

        if (value == "true" || value == "1") {
            return true;
        }
        if (value == "false" || value == "0") {
            return false;
        }

        throw std::runtime_error("Invalid boolean in XML element " + join_path(element_path)
                                 + ": " + value);
    }

private:
    [[nodiscard]] const tinyxml2::XMLElement& element(
        std::initializer_list<std::string_view> element_path) const {
        if (element_path.size() == 0) {
            throw std::invalid_argument("XML element path cannot be empty");
        }

        const tinyxml2::XMLElement* current = m_document.RootElement();
        if (current == nullptr) {
            throw std::runtime_error("XML file has no root element: " + m_path.string());
        }

        auto it = element_path.begin();
        if (std::string_view(current->Name()) != *it) {
            throw std::runtime_error("Unexpected XML root in " + m_path.string()
                                     + ". Expected " + std::string(*it)
                                     + ", got " + current->Name());
        }

        for (++it; it != element_path.end(); ++it) {
            const std::string node_name(*it);
            current = current->FirstChildElement(node_name.c_str());
            if (current == nullptr) {
                throw std::runtime_error("Missing XML element: " + join_path(element_path));
            }
        }

        return *current;
    }

    void validate_path() const {
        std::error_code error;
        const bool exists = std::filesystem::exists(m_path, error);
        if (error || !exists) {
            throw std::invalid_argument("Invalid XML path: " + m_path.string());
        }

        const bool is_regular_file = std::filesystem::is_regular_file(m_path, error);
        if (error || !is_regular_file) {
            throw std::invalid_argument("Invalid XML path: " + m_path.string());
        }
    }

    void load_document() {
        const tinyxml2::XMLError result = m_document.LoadFile(m_path.string().c_str());
        if (result != tinyxml2::XML_SUCCESS) {
            throw std::runtime_error("Failed to parse XML file " + m_path.string()
                                     + ": " + m_document.ErrorName());
        }
    }

    [[nodiscard]] static std::string trim(std::string value) {
        const auto first = std::find_if_not(value.begin(), value.end(), [](unsigned char c) {
            return std::isspace(c) != 0;
        });
        const auto last = std::find_if_not(value.rbegin(), value.rend(), [](unsigned char c) {
            return std::isspace(c) != 0;
        }).base();

        if (first >= last) {
            return {};
        }

        return std::string(first, last);
    }

    [[nodiscard]] static std::string join_path(std::initializer_list<std::string_view> element_path) {
        std::string result;
        for (std::string_view segment : element_path) {
            if (!result.empty()) {
                result += '/';
            }
            result += segment;
        }
        return result;
    }

    std::filesystem::path m_path;
    tinyxml2::XMLDocument m_document;
};

} // namespace butler::utils::parsers

#endif // BUTLER_UTILS_PARSERS_XML_PARSER_H
