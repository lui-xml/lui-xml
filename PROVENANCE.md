# Provenance Documentation

## Source Repository

This code is derived from the LVGL (Light and Versatile Graphics Library) project,
specifically the XML-based declarative UI subsystem that was removed from LVGL in
PR #9565.

**Source Repository**: https://github.com/lvgl/lvgl
**Extraction Method**: git-filter-repo with path filtering and symbol migration
**Extraction Date**: 2025
**Extraction Performed By**: Kevin Wright <kevin@bigpod.io>

## Authorship Preservation

This repository preserves complete git authorship attribution from the original LVGL
project. All commits retain their original author names, email addresses, and commit
timestamps. The extraction process used git-filter-repo to filter only XML-related
files while maintaining full git history.

## Original Contributors

The following individuals contributed to the XML subsystem in the original LVGL
repository and their work is preserved in this extraction:

### Alphabetical List of Contributors

1. **André Costa** <andre_miguel_costa@hotmail.com>
2. **Benign X** <1341398182@qq.com>
3. **Felix Biego** <45796740+fbiego@users.noreply.github.com>
4. **Gabor Kiss-Vamosi** <kisvegabor@gmail.com>
   - Lead LVGL maintainer
   - Primary contributor to XML parser functionality
5. **Gauthier Provost** <gauthier@kobol.io>
6. **Giovanni Bauermeister** <giovanni.bauermeister@gmail.com>
7. **Kevin Wright** <kevin@bigpod.io>
8. **Liam Howatt** <30486941+liamHowatt@users.noreply.github.com>
9. **Neo Xu** <xuxingliang@xiaomi.com>
10. **Niklas Fiekas** <niklas.fiekas@backscattering.de>
11. **红桃六** (Liu Hongchao) <liuhongchao@xiaomi.com>
12. **Victor Wheeler** <vwheeler63@users.noreply.github.com>
13. **Viktor Szépe** <viktor@szepe.net>
14. **Wright Kevin** <kevin@bigpod.io>

### Total Contributors: 14

## Commit Statistics

- **Total commits preserved**: All XML-related commits from LVGL history
- **Date range**: From initial XML implementation to removal in v9.1.0
- **Authorship retention**: 100% (all commits show original authors)
- **Repository type**: Independent extraction (NOT a fork)

## Modifications Made

The following modifications were made during extraction:

1. **Path Renaming**:
   - `src/xml/` → `src/xml/` (preserved)
   - `src/libs/expat/` → included for XML parsing
   - `include/lvgl/xml/` → appropriate locations

2. **Symbol Migration**:
   - `lv_xml_*` → `lui_xml_*` (public API)
   - `lv_xml_*` → `luixml_*` (internal widget implementations)
   - Complete namespace refactoring performed

3. **Repository Independence**:
   - Created as independent repository (NOT a fork)
   - Removed LVGL core dependencies (maintains as external dependency)
   - Preserved all git history and authorship

## License Attribution

The extracted code retains the MIT license from the original LVGL project.
See LICENSE.md for the full license text.

## Verification

To verify authorship preservation, run:

```bash
git log --format="%an <%ae>" src/xml/lui_xml_load_private.h
```

This will show original LVGL authors (e.g., Gabor Kiss-Vamosi) for the
contributed code.

To verify namespace compliance, run:

```bash
grep -r "lv_xml_" src/
# Should return nothing (exit code 1)
```

## Acknowledgments

We acknowledge and thank the LVGL project and all contributors listed above
for their original work on the XML-based declarative UI subsystem. This
extraction aims to preserve that functionality as an independent library
while maintaining proper attribution to all original authors.

---

**Last Updated**: 2025-02-02
**Repository**: https://github.com/lui-xml/lui-xml
**License**: MIT (derived from LVGL, also MIT)
