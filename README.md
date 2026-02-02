# Lui-XML

**Lightweight User Interface - XML**: Declarative UI for LVGL v9.1.0

## Overview

Lui-XML is a standalone extension library for LVGL that restores XML-based
declarative UI capabilities. It provides a parser and loader that allows
you to define user interfaces in XML format instead of C code.

## Features

- **Declarative UI**: Define interfaces in XML instead of imperative C code
- **Widget Support**: Support for all major LVGL widgets (button, label,
  image, slider, etc.)
- **Runtime Loading**: Load XML from strings or files at runtime
- **Extensible**: Register custom widget parsers for your own widgets
- **Namespace Isolated**: Uses `lui_xml_` namespace to prevent conflicts
  with LVGL

## Example

```xml
<button label="Click Me" x=10 y=20>
    <label text="Hello World" x=0 y=30>
</button>
```

```c
// Load and create UI from XML
lui_xml_t *parser = lui_xml_create();
lv_obj_t *ui = lui_xml_load(parser, xml_string);
lui_xml_destroy(parser);
```

## Version Coupling

Lui-XML is strictly version-coupled to LVGL:
- **Lui-XML v9.1.0-x** requires **LVGL v9.1.0**
- Other LVGL versions are not supported

## Installation

### CMake (Recommended)

```cmake
find_package(lvgl REQUIRED)
include(FetchContent)

FetchContent_Declare(
    lui_xml
    GIT_REPOSITORY https://github.com/lui-xml/lui-xml.git
    GIT_TAG        v9.1.0-1.0.0
)

FetchContent_MakeAvailable(lui_xml)

target_link_libraries(your_app PRIVATE lui::xml)
```

### ESP-IDF Component

Add to your `idf_component.yml`:

```yaml
dependencies:
  lui_xml:
    version: "9.1.0-1.0.0"
    git: https://github.com/lui-xml/lui-xml.git
```

## Documentation

See the `docs/` directory for:
- API documentation
- Migration guide from LVGL XML
- Widget reference
- Example code

## Legal

- **License**: MIT (same as LVGL)
- **Provenance**: See PROVENANCE.md for authorship and extraction details
- **Disclaimer**: See DISCLAIMER.md for project status and trademark information

## Contributing

Contributions are welcome! Please see CONTRIBUTING.md for guidelines.

## License

MIT License - see LICENSE file for details

## Acknowledgments

This project is based on XML parser code originally developed for LVGL and
preserved here after its removal from LVGL core in PR #9565. Original
authorship is preserved in the git history.
