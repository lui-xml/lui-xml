# Disclaimer and Project Independence Statement

## Project Independence

Lui-XML is an **independent open source project** that maintains XML-based
declarative UI functionality originally removed from LVGL in PR #9565.

### Relationship to LVGL

**Lui-XML is NOT:**
- A fork of the LVGL project
- Officially affiliated with LVGL Kft.
- Endorsed or maintained by the LVGL team
- A replacement for LVGL core functionality

**Lui-XML IS:**
- An independent extraction of XML parser code from LVGL git history
- A satellite library that depends on LVGL as an external dependency
- Maintained by separate contributors
- Distributed under the same MIT license as LVGL

## Trademark Notice

- "LVGL" and the LVGL logo are trademarks of LVGL Kft.
- "Lui-XML" is a separate project and is not affiliated with or endorsed by LVGL Kft.
- Use of LVGL trademarks in this documentation is for attribution purposes only.

## Dependency Requirements

Lui-XML **requires** LVGL v9.1.0 as an external dependency. This is a **strict
version coupling** - Lui-XML v9.1.0-x is designed to work ONLY with LVGL v9.1.0.

Users must:
1. Install LVGL v9.1.0 separately
2. Link Lui-XML as an additional component
3. Follow LVGL's licensing terms (MIT, with attribution)

## Support and Maintenance

- **Issues**: Report Lui-XML issues at https://github.com/lui-xml/lui-xml/issues
- **LVGL Issues**: Report LVGL issues at https://github.com/lvgl/lvgl/issues
- The Lui-XML maintainers do not provide support for LVGL core functionality

## Liability

This project is provided "as is" without warranty of any kind, express or implied.
The maintainers of Lui-XML:

- Are not responsible for damages arising from use of this software
- Do not guarantee compatibility with future LVGL versions
- Do not provide official support for integration into user projects
- Are not liable for any trademark or copyright infringement claims related to LVGL

## Attribution Requirements

As a condition of using this software, users must:

1. Preserve all copyright notices and attribution in the source code
2. Acknowledge both LVGL and Lui-XML in project documentation
3. Comply with the MIT license terms of both projects
4. Not remove or alter the PROVENANCE.md file

## Version Compatibility

**IMPORTANT**: Lui-XML v9.1.0-x is strictly coupled to LVGL v9.1.0.

- **Supported**: LVGL v9.1.0
- **Not Supported**: LVGL v9.0.x, v9.2.x, or any other version
- **Future versions**: Will be released for corresponding LVGL versions

Use with unsupported LVGL versions may result in:
- Compilation failures
- Runtime errors
- Undefined behavior
- Memory corruption

## Legal Status

This extraction was performed in accordance with:
- The MIT license terms of the original LVGL project
- Git authorship preservation requirements
- Open source best practices for code extraction

All extracted code retains the MIT license from LVGL. See LICENSE.md for details.

## Contact

For questions about this project's independence or legal status, contact:
- GitHub Issues: https://github.com/lui-xml/lui-xml/issues
- Maintainer: Kevin Wright <kevin@bigpod.io>

---

**Last Updated**: 2025-02-02
**Version**: 9.1.0-1.0.0-dev
**License**: MIT
