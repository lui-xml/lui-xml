# XML Schema Files

This directory contains XML schema and template files extracted from LVGL. These files
define the API structure for each widget type when using XML-based UI definitions.

## Origin

Extracted from LVGL repository at commit `eec91d9f` (PR #9565 - feat(xml): remove the XML parser and loader).
All git history and authorship has been preserved.

## File Structure

- **globals.xml** - Global type definitions (lv_state, lv_part, lv_event, etc.)
- **lv_*.xml** - Widget-specific API definitions

## Purpose

These XML files serve as:
1. **API Documentation** - Complete reference of available properties, flags, and events for each widget
2. **Schema Reference** - Defines valid XML structure for each widget type
3. **Tool Input** - Can be used by code generators, IDEs, or documentation tools

## Example

Each `lv_*.xml` file defines the available elements and attributes for that widget:

```xml
<!--
Example
<lv_obj width="100" hidden="true"/>
-->

<widget>
    <api>
        <element name="width" type="int" help="Width of the widget"/>
        <element name="hidden" type="enum:lv_obj_flag" help="Hide the widget"/>
        ...
    </api>
</widget>
```

## History

These files contain 81 commits of history from the original LVGL repository, tracking
the evolution of the XML schema from its initial implementation through removal in v9.1.

Use `git log --follow -- xmls/<file>` to see the full history of any file.

## License

MIT License - same as LVGL and Lui-XML. Authorship preserved in git history.
