# Migration Guide: LVGL v9.0 XML to Lui-XML

**Version**: Lui-XML v9.1.0-1.0.0
**Source**: LVGL v9.0 XML subsystem
**Purpose**: Guide for migrating LVGL v9.0 XML-based UI code to Lui-XML

---

## Overview

LVGL removed XML-based declarative UI support in PR #9565. Lui-XML restores this functionality as an independent library while maintaining compatibility with LVGL v9.x.

This guide covers:
- Symbol namespace changes
- Automated migration script
- API changes and differences
- Before/after code examples

---

## Symbol Namespace Migration

### Public API Symbols

The public XML parser API has been renamed from `lv_xml_*` to `lui_xml_*`:

| LVGL v9.0 Symbol | Lui-XML Symbol | Notes |
|------------------|-----------------|-------|
| `lv_xml_parser_create` | `lui_xml_create` | Parser instantiation |
| `lv_xml_parser_destroy` | `lui_xml_destroy` | Parser cleanup |
| `lv_xml_load` | `lui_xml_load` | Load XML from string |
| `lv_xml_load_file` | `lui_xml_load_file` | Load XML from file |
| `lv_xml_get_last_error` | `lui_xml_get_last_error` | Get error code |
| `lv_xml_get_error_message` | `lui_xml_get_error_message` | Get error text |

### Internal Widget Symbols

Internal widget symbols have been renamed from `lv_xml_*` to `luixml_*`:

| LVGL v9.0 Symbol | Lui-XML Symbol | Widget Type |
|------------------|-----------------|-------------|
| `lv_xml_button` | `luixml_button` | Button widget |
| `lv_xml_label` | `luixml_label` | Label widget |
| `lv_xml_image` | `luixml_image` | Image widget |
| `lv_xml_arc` | `luixml_arc` | Arc widget |
| `lv_xml_bar` | `luixml_bar` | Bar/progress widget |
| `lv_xml_slider` | `luixml_slider` | Slider widget |
| `lv_xml_switch` | `luixml_switch` | Switch widget |
| `lv_xml_checkbox` | `luixml_checkbox` | Checkbox widget |
| `lv_xml_dropdown` | `luixml_dropdown` | Dropdown (roller) widget |
| `lv_xml_roller` | `luixml_roller` | Roller widget |
| `lv_xml_textarea` | `luixml_textarea` | Text area widget |
| `lv_xml_keyboard` | `luixml_keyboard` | Keyboard widget |
| `lv_xml_buttonmatrix` | `luixml_buttonmatrix` | Button matrix widget |
| `lv_xml_chart` | `luixml_chart` | Chart widget |
| `lv_xml_calendar` | `luixml_calendar` | Calendar widget |
| `lv_xml_canvas` | `luixml_canvas` | Canvas widget |
| `lv_xml_tabview` | `luixml_tabview` | Tabview widget |
| `lv_xml_spinbox` | `luixml_spinbox` | Spinbox widget |
| `lv_xml_spinner` | `luixml_spinner` | Spinner widget |
| `lv_xml_scale` | `luixml_scale` | Scale widget |
| `lv_xml_table` | `luixml_table` | Table widget |
| `lv_xml_imagebutton` | `luixml_imagebutton` | Image button widget |
| `lv_xml_qrcode` | `luixml_qrcode` | QR code widget |
| `lv_xml_spangroup` | `luixml_spangroup` | Span group widget |

---

## Automated Migration Script

### sed Script for Symbol Migration

The following `sed` script will automatically migrate your code from LVGL v9.0 XML symbols to Lui-XML symbols:

```bash
#!/bin/bash
# migrate_lui_xml.sh - Automated migration from LVGL v9.0 XML to Lui-XML
# Usage: ./migrate_lui_xml.sh your_file.c

# Backup original file
cp "$1" "$1.backup"

# Public API symbol migration
sed -i.bak \
    -e 's/lv_xml_parser_create/lui_xml_create/g' \
    -e 's/lv_xml_parser_destroy/lui_xml_destroy/g' \
    -e 's/lv_xml_load/lui_xml_load/g' \
    -e 's/lv_xml_load_file/lui_xml_load_file/g' \
    -e 's/lv_xml_get_last_error/lui_xml_get_last_error/g' \
    -e 's/lv_xml_get_error_message/lui_xml_get_error_message/g' \
    "$1"

# Internal widget symbol migration
sed -i.bak2 \
    -e 's/lv_xml_button/luixml_button/g' \
    -e 's/lv_xml_label/luixml_label/g' \
    -e 's/lv_xml_image/luixml_image/g' \
    -e 's/lv_xml_arc/luixml_arc/g' \
    -e 's/lv_xml_bar/luixml_bar/g' \
    -e 's/lv_xml_slider/luixml_slider/g' \
    -e 's/lv_xml_switch/luixml_switch/g' \
    -e 's/lv_xml_checkbox/luixml_checkbox/g' \
    -e 's/lv_xml_dropdown/luixml_dropdown/g' \
    -e 's/lv_xml_roller/luixml_roller/g' \
    -e 's/lv_xml_textarea/luixml_textarea/g' \
    -e 's/lv_xml_keyboard/luixml_keyboard/g' \
    -e 's/lv_xml_buttonmatrix/luixml_buttonmatrix/g' \
    -e 's/lv_xml_chart/luixml_chart/g' \
    -e 's/lv_xml_calendar/luixml_calendar/g' \
    -e 's/lv_xml_canvas/luixml_canvas/g' \
    -e 's/lv_xml_tabview/luixml_tabview/g' \
    -e 's/lv_xml_spinbox/luixml_spinbox/g' \
    -e 's/lv_xml_spinner/luixml_spinner/g' \
    -e 's/lv_xml_scale/luixml_scale/g' \
    -e 's/lv_xml_table/luixml_table/g' \
    -e 's/lv_xml_imagebutton/luixml_imagebutton/g' \
    -e 's/lv_xml_qrcode/luixml_qrcode/g' \
    -e 's/lv_xml_spangroup/luixml_spangroup/g' \
    "$1"

# Clean up backup files
rm -f "$1.bak" "$1.bak2"

echo "Migrated $1"
echo "Original file backed up as $1.backup"
```

### How to Use

1. Save the script as `migrate_lui_xml.sh`
2. Make it executable: `chmod +x migrate_lui_xml.sh`
3. Run on your code: `./migrate_lui_xml.sh your_file.c`
4. Review the changes: `diff your_file.c.backup your_file.c`
5. If satisfied, delete backup: `rm your_file.c.backup`

### Migrating Entire Project

To migrate an entire project at once:

```bash
#!/bin/bash
# migrate_project.sh - Migrate entire project

for file in $(find . -name "*.c" -o -name "*.h"); do
    ./migrate_lui_xml.sh "$file"
done

echo "Project migration complete!"
echo "Review changes before committing."
```

---

## API Changes and Differences

### Header Files

**LVGL v9.0:**
```c
#include "../../lvgl.h"
```

**Lui-XML:**
```c
#include <lvgl.h>
#include "lui_xml_load.h"
```

### Parser Creation

**LVGL v9.0:**
```c
lv_xml_parser_t *parser = lv_xml_parser_create();
```

**Lui-XML:**
```c
lui_xml_t *parser = lui_xml_create();
```

### Error Handling

**LVGL v9.0:**
```c
if (lv_xml_load(parser, xml_string) == NULL) {
    // Handle error
}
```

**Lui-XML:**
```c
if (lui_xml_load(parser, xml_string) == NULL) {
    // Handle error
    lui_xml_error_t error = lui_xml_get_last_error(parser);
    const char *msg = lui_xml_get_error_message(parser, error);
    fprintf(stderr, "XML load error: %s\n", msg);
}
```

### No Breaking Changes

The migration is purely mechanical (symbol renaming). All functionality remains the same:
- Same XML syntax
- Same widget types
- Same property names
- Same parser behavior

---

## Before/After Examples

### Example 1: Simple Button UI

**LVGL v9.0 XML:**
```c
#include "../../lvgl.h"

void create_button_ui(void) {
    lv_xml_parser_t *parser = lv_xml_parser_create();

    const char *xml = "<button text=\"Click Me\" pos=\"10,10\" size=\"100,50\"/>";
    lv_obj_t *ui = lv_xml_load(parser, xml);

    lv_xml_parser_destroy(parser);
}
```

**Lui-XML:**
```c
#include <lvgl.h>
#include "lui_xml_load.h"

void create_button_ui(void) {
    lui_xml_t *parser = lui_xml_create();

    const char *xml = "<button text=\"Click Me\" pos=\"10,10\" size=\"100,50\"/>";
    lv_obj_t *ui = lui_xml_load(parser, xml);

    lui_xml_destroy(parser);
}
```

### Example 2: Nested Widgets

**LVGL v9.0 XML:**
```c
const char *xml =
"<button pos=\"10,10\" size=\"200,100\">"
"  <label text=\"Button Label\" pos=\"10,10\"/>"
"</button>";

lv_obj_t *ui = lv_xml_load(parser, xml);
```

**Lui-XML:**
```c
const char *xml =
"<button pos=\"10,10\" size=\"200,100\">"
"  <label text=\"Button Label\" pos=\"10,10\"/>"
"</button>";

lv_obj_t *ui = lui_xml_load(parser, xml);
```

**Note**: XML syntax is identical - only the function names changed.

### Example 3: Error Handling

**LVGL v9.0 XML:**
```c
lv_obj_t *ui = lv_xml_load(parser, xml);
if (ui == NULL) {
    fprintf(stderr, "Failed to load XML\n");
}
```

**Lui-XML:**
```c
lv_obj_t *ui = lui_xml_load(parser, xml);
if (ui == NULL) {
    lui_xml_error_t error = lui_xml_get_last_error(parser);
    const char *msg = lui_xml_get_error_message(parser, error);
    fprintf(stderr, "XML load error: %s\n", msg);
}
```

### Example 4: File Loading

**LVGL v9.0 XML:**
```c
lv_obj_t *ui = lv_xml_load_file(parser, "/spiffs/ui/main.xml");
```

**Lui-XML:**
```c
lv_obj_t *ui = lui_xml_load_file(parser, "/spiffs/ui/main.xml");
```

---

## Build System Integration

### CMake Changes

**LVGL v9.0 (built-in):**
No configuration needed - XML was part of LVGL.

**Lui-XML (external dependency):**
```cmake
# Find LVGL
find_package(lvgl REQUIRED)

# Add Lui-XML via FetchContent
include(FetchContent)
FetchContent_Declare(
    lui_xml
    GIT_REPOSITORY https://github.com/lui-xml/lui-xml.git
    GIT_TAG v9.1.0-1.0.0
)

# Lui-XML will automatically find and link LVGL
add_subdirectory(${lui_xml_SOURCE_DIR})

# Link your application
target_link_libraries(your_app PRIVATE lui::xml)
```

### ESP-IDF Changes

**LVGL v9.0 (built-in):**
```ini
; dependencies.ini
dependencies:
    lvgl/lvgl "^9.0.0"
```

**Lui-XML (external component):**
```yaml
; main/idf_component.yml
dependencies:
    espressif/lvgl_lvgl_port "^9.0.0"
  lui_xml:
    git: https://github.com/lui-xml/lui-xml.git
    version: "^9.1.0.1"
```

---

## Testing Your Migration

### 1. Compile Test

After running the migration script, verify your code compiles:

```bash
cd your_project
make clean
make
```

### 2. Visual Inspection

Review key files to ensure migration was successful:

```bash
grep -r "lv_xml_" src/
# Should return nothing (all symbols migrated)

grep -r "lui_xml_" src/
# Should show new symbols
```

### 3. Runtime Test

Run your application and verify UI loads correctly:

```bash
./your_app
```

### 4. Validation Checklist

- [ ] All `lv_xml_*` symbols replaced
- [ ] Code compiles without errors
- [ ] Application starts without crashes
- [ ] UI renders correctly
- [ ] XML files load successfully
- [ ] Error handling works as expected

---

## Troubleshooting

### Issue: Compilation Errors After Migration

**Problem**: Undefined references to `lv_xml_*` symbols.

**Solution**:
1. Verify you linked against `lui::xml` target
2. Check that Lui-XML is properly initialized before use
3. Ensure all source files were migrated

### Issue: Runtime Crashes

**Problem**: Application crashes when loading XML.

**Solution**:
1. Verify LVGL is initialized before Lui-XML
2. Check for NULL return values from `lui_xml_load()`
3. Review error messages with `lui_xml_get_last_error()`
4. Ensure XML syntax is valid

### Issue: Missing Widgets

**Problem**: Some widgets don't render.

**Solution**:
1. Verify widget is enabled in LVGL configuration
2. Check that XML widget name matches supported widgets
3. Review console for error messages

---

## Additional Resources

- **GitHub Repository**: https://github.com/lui-xml/lui-xml
- **API Documentation**: See `docs/html/` (run `make docs` to generate)
- **Issues**: Report at https://github.com/lui-xml/lui-xml/issues
- **LVGL Documentation**: https://docs.lvgl.io/

---

## Need Help?

If you encounter issues not covered in this guide:

1. Check the [GitHub Issues](https://github.com/lui-xml/lui-xml/issues) for similar problems
2. Search the [LVGL Forums](https://forum.lvgl.io/)
3. Open a new issue with:
   - LVGL version
   - Lui-XML version
   - Code example
   - Error message
   - Steps to reproduce

---

**Last Updated**: 2025-02-02
**Lui-XML Version**: 9.1.0-1.0.0
**Migration From**: LVGL v9.0 XML
