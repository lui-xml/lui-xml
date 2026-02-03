# XML Documentation

This directory contains the complete XML documentation extracted from LVGL.
These are the official user guide and reference materials for using LVGL's
XML-based declarative UI system.

## Origin

Extracted from LVGL repository at commit `cd293b4f7`.
All git history and authorship has been preserved.

## Documentation Structure

```
docs/src/xml/
├── intro.rst              - Introduction to XML in LVGL
├── index.rst              - Main documentation index
├── learn_by_examples.rst  - Tutorial and examples
│
├── xml/                   - XML syntax and concepts
│   ├── overview.rst       - XML overview
│   ├── syntax.rst         - XML syntax reference
│   └── license.rst        - License information
│
├── ui_elements/           - UI element documentation
│   ├── api.rst            - Complete API reference
│   ├── widgets.rst        - Widget documentation
│   ├── styles.rst         - Styling reference
│   ├── events.rst         - Event handling
│   ├── animations.rst     - Animation support
│   ├── screens.rst        - Screen management
│   ├── consts.rst         - Constants reference
│   ├── components.rst     - Component system
│   ├── view.rst           - View system
│   ├── preview.rst        - Preview functionality
│   └── index.rst
│
├── features/              - Advanced features
│   ├── subjects.rst       - Data binding subjects
│   ├── translations.rst   - Translation support
│   ├── tests.rst          - Testing framework
│   └── index.rst
│
├── integration/           - Platform integration
│   ├── xml.rst            - General XML integration
│   ├── c_code.rst         - C code integration
│   ├── arduino.rst        - Arduino platform
│   ├── zephyr.rst         - Zephyr RTOS
│   ├── reneas-dev-tools.rst - Renesas toolchain
│   └── index.rst
│
├── tools/                 - Development tools
│   ├── cli.rst            - Command-line tools
│   ├── figma.rst          - Figma integration
│   ├── online_share.rst   - Online sharing
│   └── index.rst
│
└── assets/                - Asset management
    ├── fonts.rst          - Font handling
    ├── images.rst         - Image handling
    └── index.rst
```

## Using This Documentation

These files are written in reStructuredText (rst) format and are intended to be
built with Sphinx, which is the same documentation system used by LVGL.

### Build HTML Documentation

If you have Sphinx installed:

```bash
cd docs
pip install -r requirements.txt  # Install Sphinx dependencies
make html
```

The generated HTML will be in `docs/_build/html/xml/`.

### Read Directly

You can read the .rst files directly in any text editor or GitHub's web interface.
The reStructuredText format is human-readable.

## Key Sections

- **Start here**: `intro.rst` - Introduction to XML in LVGL
- **API Reference**: `ui_elements/api.rst` - Complete API documentation
- **Integration Guide**: `integration/xml.rst` - How to integrate XML parser
- **Examples**: `learn_by_examples.rst` - Tutorial with examples

## Relationship to Lui-XML

This documentation was written for LVGL's built-in XML parser. When using Lui-XML:
- All concepts and syntax remain the same
- API functions use `lui_xml_*` prefix instead of `lv_xml_*`
- Refer to `MIGRATION.md` for symbol mapping

## History

These files contain the complete documentation history from LVGL, tracking
the evolution of the XML system from its initial implementation through
removal in v9.1.

Use `git log --follow -- docs/src/xml/<file>` to see the full history of any file.

## License

MIT License - same as LVGL and Lui-XML. Authorship preserved in git history.
