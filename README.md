# Lui-XML

**Lightweight User Interface - XML**: Declarative UI for LVGL v9.x

## Overview

Lui-XML is a standalone extension library for LVGL that restores XML-based
declarative UI capabilities. It provides a parser and loader that allows
you to define user interfaces in XML format instead of C code.

> **Note**: LVGL removed XML-based declarative UI in PR #9565. Lui-XML
> preserves this functionality as an independent library for LVGL v9.x.

## Features

- **Declarative UI**: Define interfaces in XML instead of imperative C code
- **Widget Support**: Support for all major LVGL widgets (button, label,
  image, slider, switch, checkbox, dropdown, chart, calendar, etc.)
- **Runtime Loading**: Load XML from strings or files at runtime
- **Extensible**: Register custom widget parsers for your own widgets
- **Namespace Isolated**: Uses `lui_xml_*` (public) and `luixml_*` (internal) namespaces
- **Version Support**: Compatible with LVGL v9.0 through v9.5+

## Quick Start

```xml
<!-- Define your UI in XML -->
<button pos="10" y="20" width="100" height="50">
    <label text="Click Me" pos="0" y="15"/>
</button>
```

```c
// Load and create UI from XML
#include <lvgl.h>
#include "lui_xml_load.h"

lui_xml_t *parser = lui_xml_create();
lv_obj_t *ui = lui_xml_load(parser, xml_string);
lui_xml_destroy(parser);
```

## Version Compatibility

Lui-XML supports LVGL v9.0+:

| Lui-XML Version | LVGL Version | Status |
|-----------------|--------------|--------|
| v9.1.0-x | v9.0 - v9.5 | ✅ Tested |
| v9.1.0-x | v9.6+ | ⚠️  Untested (may work) |
| v9.1.0-x | v8.x or v10.x | ❌ Not compatible |

**Note**: Lui-XML v9.1.0-x is strictly coupled to LVGL v9.x major version.

## Installation

### CMake (Recommended for Linux/Embedded)

```cmake
cmake_minimum_required(VERSION 3.16)

# Find LVGL first
find_package(lvgl REQUIRED)

# Add Lui-XML via FetchContent
include(FetchContent)

FetchContent_Declare(
    lui_xml
    GIT_REPOSITORY https://github.com/lui-xml/lui-xml.git
    GIT_TAG        v9.1.0-1.0.0
)

FetchContent_MakeAvailable(lui_xml)

# Link your application
target_link_libraries(your_app PRIVATE lui::xml)
```

### ESP-IDF (ESP32/ESP-Series)

Create or update `main/idf_component.yml`:

```yaml
dependencies:
  # LVGL port for ESP-IDF
  espressif/esp_lvgl_port: "^1.0.0"

  # Lui-XML component
  lui_xml:
    git: https://github.com/lui-xml/lui-xml.git
    version: "^9.1.0.1"
```

Build your project:

```bash
idf.py build
idf.py flash monitor
```

### Manual Installation

```bash
# Clone repository
git clone https://github.com/lui-xml/lui-xml.git
cd lui-xml

# Build with CMake
mkdir build && cd build
cmake ..
make
```

## Documentation

- **Migration Guide**: See [MIGRATION.md](MIGRATION.md) for migrating from LVGL v9.0 XML
- **API Documentation**: Run `make docs` to generate Doxygen HTML
- **Legal**: See [PROVENANCE.md](PROVENANCE.md) and [DISCLAIMER.md](DISCLAIMER.md)

### Quick Reference

**Public API Functions**:
- `lui_xml_create()` - Create parser instance
- `lui_xml_load()` - Load XML from string
- `lui_xml_load_file()` - Load XML from file
- `lui_xml_get_last_error()` - Get error code
- `lui_xml_destroy()` - Destroy parser

**Supported Widgets**:
- Button, Label, Image
- Arc, Bar, Slider, Switch
- Checkbox, Dropdown, Roller
- Textarea, Keyboard, Button Matrix
- Chart, Calendar, Canvas
- Tabview, Spinbox, Spinner
- Scale, Table, Image Button
- QR Code, Span Group

## Example Projects

See the `examples/` directory for complete examples:
- **Simple Button**: Basic button with label
- **Nested Layout**: Complex nested widget layout
- **File Loading**: Load XML from filesystem

## Build Status

[![CI/CD](https://github.com/lui-xml/lui-xml/workflows/CI/badge.svg)](https://github.com/lui-xml/lui-xml/actions)

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests for new functionality
5. Submit a pull request

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Legal

- **License**: MIT (same as LVGL) - see [LICENSE.md](LICENSE.md)
- **Provenance**: See [PROVENANCE.md](PROVENANCE.md) for authorship and extraction details
- **Disclaimer**: See [DISCLAIMER.md](DISCLAIMER.md) for project status and trademark information

## License

MIT License - see [LICENSE.md](LICENSE.md) for details

## Acknowledgments

This project is based on XML parser code originally developed for LVGL and
preserved here after its removal from LVGL core in PR #9565. Original
authorship is fully preserved in the git history.

**Original Contributors**: See [PROVENANCE.md](PROVENANCE.md) for complete list.

---

**Project**: https://github.com/lui-xml/lui-xml
**Version**: 9.1.0-1.0.0
**Derived from**: LVGL v9.1.0
**License**: MIT
