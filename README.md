# Lui-XML

**Lightweight User Interface - XML**: Declarative UI for LVGL v9.x

## Overview

Once uon a time, the [LVGL]((https://github.com/lvgl/lvgl) library contained an open-source 
XML-based declarative UI capabiliy. LVGL Kft decided to remove it in [lvgl/lvgl#9565](https://github.com/lvgl/lvgl/pull/9565)
for business reasons.

Lui-XML is an independent standalone extension library for LVGL v9.x that restores that code, providing the same parser and 
loader that allows you to define user interfaces in XML format instead of C code.

**Important Note**

It is important to note the folowing: A [license document](https://github.com/lvgl/lvgl/pull/8984/changes/d52d7c3696934d899a0381c9140f26ea093e6cba) related 
to XML in the LVGL UI library was added to the docs in its repository. 

The rough history of that document is as follows:

- Although the date of the license states June 2025, it was never made public until October 1, 2025
- On November 27, 2025 that document was moved
- On February 3, 2026 LVGL Kft requested its inclusion in this repository (and in good faith it was)

Due to the extraction method, in the history of this repository it shows as being added November 27, 2025 rather than October 1, 2025.


## Features

- **Declarative UI**: Define interfaces in XML instead of imperative C code
- **Widget Support**: Support for all major LVGL widgets (button, label,
  image, slider, switch, checkbox, dropdown, chart, calendar, etc.)
- **Runtime Loading**: Load XML from strings or files at runtime
- **Extensible**: Register custom widget parsers for your own widgets
- **Namespace Isolated**: Uses `lui_xml_*` (public) and `luixml_*` (internal) namespaces
- **Version Support**: Compatible with LVGL v9.x

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

Lui-XML v9.1.0-x is compatible with LVGL v9.x series.

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

