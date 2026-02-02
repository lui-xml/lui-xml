# Requirements Analysis for Lui-XML

**Purpose**: How to approach, understand, and document Lui-XML requirements correctly.

**Key Principle**: Never write spec requirements without understanding the specification document first.

---

## The Requirements Process

### For Lui-XML: Where Requirements Come From

**Source 1: Specification Document** (PRIMARY)
- Location: `docs/planning/specifications/1/README.md`
- Contains: Technical architecture, problem statement, proposed solution
- What to extract: Technical requirements, performance criteria, legal constraints

**Source 2: Implementation Roadmap** (PRIMARY)
- **Phase 1**: Archaeology & Extraction (code extraction from LVGL)
- **Phase 2**: Compatibility Engineering (shim layer)
- **Phase 3**: Build System Hardening (CMake/ESP-IDF)
- **Phase 4**: Testing & Validation (unit tests, integration tests)
- **Phase 5**: Documentation & Release (API docs, migration guides)
- What to extract: Success criteria, deliverables

**Source 3: OpenSpec Existing Specs** (REFERENCE)
- Location: `openspec/specs/*/spec.md`
- Contains: Existing specifications for capabilities
- What to extract: Dependencies, constraints, patterns to follow

---

## Requirements Analysis Process

### Step 1: Read the Specification Document

**Document**: `docs/planning/specifications/1/README.md`

**What to extract**:
```markdown
## Specification Requirements Analysis

### Section 3.2: Namespace Strategy
**Key Requirements**:
- All symbols use lui_ prefix for public APIs
- Internal widgets use luixml_ prefix
- No lv_xml_ symbols to prevent collision

**Constraints**:
- Namespace isolation mandatory
- LVGL symbol collision must be prevented
- Forward compatibility with LVGL v10.x

### Section 4.2: Build System Integration
**Key Requirements**:
- CMake FetchContent support
- ESP-IDF component support
- LVGL target detection

**Constraints**:
- Must detect existing lvgl target
- Must fail gracefully if LVGL not found
```

---

### Step 2: Read Implementation Roadmap

**Phase Documents**:
```markdown
### Phase 1: Archaeology & Extraction
**Purpose**: Extract XML subsystem from LVGL git history

**Success Criteria**:
- Complete git history preserved
- All files renamed to lui_xml_ namespace
- No LVGL core files included
- PROVENANCE.md generated

**Key Requirements**:
- Use git-filter-repo for extraction
- Preserve authorship attribution
- Namespace migration complete
```

---

### Step 3: Document Requirements

**Template**:
```markdown
# Requirements: [Capability Name]

## Specification Requirements

### From Specification Section X.Y: [Section Title]

**Explicit Requirements**:
- [Requirement 1]
- [Requirement 2]

**Implicit Requirements**:
- [Derived requirement 1]

**Constraints**:
- [Constraint 1]

## Roadmap Phases

### Phase: [Phase N]
**Purpose**: [From phase description]
**Success Criteria**: [From phase description]

## Requirements to Scenarios Mapping

### Requirement 1: [Name]
**Source**: Specification Section X.Y, Phase N

**Draft Requirement**: The system SHALL [requirement]

**Draft Scenarios**:
#### Scenario: [Name]
- **GIVEN** [condition]
- **WHEN** [action]
- **THEN** [result]

## Constraints
- **Technical**: [From specification]
- **Legal**: [MIT license, provenance]

## Dependencies
- **Required specs**: [From OpenSpec]
```

---

## Requirements Tracking

### During Spec Development

**Track which requirements are complete**:
```markdown
## Spec Development Status

### Specification Coverage
- [ ] Section 3.2: Namespace → 1 requirement written
- [ ] Section 4.2: Build System → 2 requirements written

**Status**: ⚠️ IN PROGRESS

### Roadmap Phase Coverage
- [ ] Phase 1 → 2 requirements written
- [ ] Phase 2 → 1 requirement written

**Status**: ⚠️ IN PROGRESS
```

---

## Common Requirements Mistakes

### ❌ Mistake 1: Reading Implementation Plans Instead of Specification

**Wrong**:
```
1. Read implementation roadmap tasks
2. Write spec requirements
3. Mark spec complete
```

**Correct**:
```
1. Read specification (PRIMARY source)
2. Read roadmap phases (context)
3. Extract requirements
4. Map to scenarios
5. Validate coverage
6. Mark spec complete
```

---

### ❌ Mistake 2: Inventing Requirements

**Wrong**:
```
I think we need feature X.
I'll add a requirement for feature X.
```

**Correct**:
```
From specification Section 3.2:
"All symbols use lui_ prefix for public APIs"

Add requirement:
### Requirement: Namespace Isolation
The system SHALL use lui_ prefix for all public APIs.
```

---

### ❌ Mistake 3: Ignoring Constraints

**Wrong**:
```
Requirement: The system SHALL parse XML.

[No constraints mentioned]
```

**Correct**:
```
Requirement: The system SHALL parse LVGL XML markup within 2 seconds
using < 4 KB heap on ESP32-C3.

**Constraints**:
- Performance: ≤ 2 seconds
- Memory: ≤ 4 KB heap
- Platform: ESP32-C3 or equivalent
```

---

## Requirements Checklist

**Before starting spec development**:

### Specification Document
- [ ] Read all relevant specification sections
- [ ] Document explicit requirements
- [ ] Document implicit requirements
- [ ] Document constraints
- [ ] Document legal requirements (MIT, provenance)

### Roadmap Phases
- [ ] Read relevant phases
- [ ] Document success criteria
- [ ] Document deliverables

### Requirements Document
- [ ] Specification requirements listed
- [ ] Roadmap phases mapped
- [ ] Requirements categorized
- [ ] Constraints identified
- [ ] Dependencies identified

**Only proceed when ALL checked.**

---

## Summary

**Requirements come from specification document and roadmap, not implementation plans.**

**Process**:
1. Read specification (technical requirements, constraints)
2. Read roadmap phases (deliverables, success criteria)
3. Document requirements explicitly
4. Map requirements to scenarios
5. Validate specification coverage
6. Validate roadmap coverage

**Never write spec requirements without understanding specification first.**

---

**Next Steps**:
1. Read all specification sections for your capability
2. Read relevant roadmap phases
3. Document requirements in requirements analysis document
4. Map requirements to scenarios
5. Write spec.md with all requirements and scenarios
6. Validate specification coverage is 100%
