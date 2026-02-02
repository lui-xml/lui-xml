# Requirements Analysis for Implementation

**Purpose**: How to analyze OpenSpec requirements to plan and execute implementation.

---

## Overview

Requirements analysis is the critical first step before writing code. This guide explains how to extract implementation details from OpenSpec specifications.

---

## Reading Requirements

### Requirement Format

OpenSpec requirements follow this format:

```markdown
### Requirement: [Name]

The system SHALL [complete requirement].

**Specification Reference**: Section X.Y
**Roadmap Phase**: Phase N

#### Scenario: [Scenario Name]
- **GIVEN** [precondition]
- **WHEN** [action]
- **THEN** [expected outcome]
- **AND** [additional conditions]
```

### Extraction Checklist

For each requirement, extract:

**Functional Requirements** (what it does):
- [ ] What is the system supposed to do?
- [ ] What are the inputs?
- [ ] What are the outputs?

**Non-Functional Requirements** (how it does it):
- [ ] Namespace constraints (lui_/luixml_)
- [ ] Build system constraints (CMake, ESP-IDF)
- [ ] Legal constraints (MIT, provenance)
- [ ] Performance constraints (if applicable)

**Acceptance Criteria** (how to verify):
- [ ] Success scenarios (happy path)
- [ ] Error scenarios (edge cases)

---

## Breaking Down Requirements

### Example 1: Namespace Isolation Requirement

**Specification**:
```markdown
### Requirement: Namespace Isolation

The system SHALL use `lui_` prefix for all public APIs and `luixml_` prefix
for internal widget bindings to prevent collision with LVGL symbols.

#### Scenario: Parser Initialization
- **GIVEN** Lui-XML library is loaded
- **WHEN** lui_xml_create() is called
- **THEN** an XML parser instance is created
- **AND** default widget parsers are registered with luixml_ prefix
- **AND** no symbols use lv_xml_ prefix (forbidden)
```

**Extracted Information**:

**Functional**:
- Input: None (initialization)
- Output: Parser instance with registered widgets
- Operation: Create parser, register widgets

**Non-Functional**:
- Namespace: lui_ for public APIs
- Namespace: luixml_ for internal widgets
- Constraint: NO lv_xml_ symbols (forbidden)

**Acceptance Criteria**:
- Success: Parser created, widgets registered
- Constraint: lui_ prefix used
- Constraint: luixml_ prefix used
- Constraint: lv_xml_ NOT used

**Implementation Plan**:
1. Create lui_xml_create() function
2. Implement parser structure
3. Create luixml_register_button(), luixml_register_label(), etc.
4. Verify no lv_xml_ symbols exist

---

### Example 2: Build System Integration Requirement

**Specification**:
```markdown
### Requirement: LVGL Target Detection

The system SHALL detect whether an LVGL target exists and fail gracefully
if it does not.

#### Scenario: LVGL Target Found
- **GIVEN** CMake project includes LVGL
- **WHEN** Lui-XML is configured
- **THEN** build succeeds with message "Integrating with existing LVGL target"

#### Scenario: LVGL Target Missing
- **GIVEN** CMake project does not include LVGL
- **WHEN** Lui-XML is configured
- **THEN** build fails with error "Lui-XML requires LVGL target"
```

**Extracted Information**:

**Functional**:
- Input: CMake configuration state
- Output: Build success or failure
- Operation: Detect LVGL target

**Non-Functional**:
- Build system: CMake
- Error handling: Graceful failure with clear message

**Acceptance Criteria**:
- Success: Build succeeds when LVGL present
- Error: Build fails when LVGL missing
- Constraint: Error message must be clear

**Implementation Plan**:
1. Add CMake check for LVGL target
2. Add success message when target found
3. Add FATAL_ERROR when target missing
4. Test both scenarios

---

## Scenario Analysis

### Scenario Format

```markdown
#### Scenario: [Name]
- **GIVEN** [precondition]
- **WHEN** [action]
- **THEN** [expected outcome]
- **AND** [additional conditions as needed]
```

### Mapping Scenarios to Tests

Each scenario becomes a test case:

| Scenario Element | Test Component |
|-----------------|---------------|
| **GIVEN** | Setup/Preconditions |
| **WHEN** | Action/Trigger |
| **THEN** | Assertion/Outcome |
| **AND** | Additional Assertions |

---

## Constraint Analysis

### Types of Constraints

#### 1. Namespace Constraints (Lui-XML specific)

**Format**: "MUST use [prefix] prefix"

**Examples**:
- "Public APIs MUST use lui_ prefix"
- "Internal widgets MUST use luixml_ prefix"
- "MUST NOT use lv_xml_ prefix (collision risk)"

**How to Satisfy**:
1. Use grep to verify no forbidden symbols
2. Check all function names use correct prefix
3. Verify during code review

#### 2. Build System Constraints

**Format**: "MUST support [build system]"

**Examples**:
- "MUST support CMake 3.15+"
- "MUST support ESP-IDF component"
- "MUST detect LVGL target"

**How to Satisfy**:
1. Test CMake integration
2. Test ESP-IDF integration
3. Verify LVGL detection logic

#### 3. Legal Constraints

**Format**: "MUST preserve [attribute]"

**Examples**:
- "MUST preserve git authorship"
- "MUST maintain MIT license"
- "MUST document provenance"

**How to Satisfy**:
1. Use git-filter-repo with --preserve-commit-author
2. Include PROVENANCE.md
3. Include LICENSE file

---

## Extracting Implementation Tasks

### From Requirements to Tasks

**Requirement**: "The system SHALL create an XML parser that loads LVGL UI definitions."

**Extracted Tasks**:
1. Implement XML parsing (lui_xml_parser.c)
2. Implement widget loading (luixml_button.c, etc.)
3. Implement lui_xml_load() function
4. Register default widgets
5. Add error handling for invalid XML

### Organizing Tasks

**By Priority**:
1. Critical path (core functionality)
2. Error handling
3. Namespace compliance
4. Documentation

**By Dependency**:
1. Foundation (no dependencies)
2. Core features
3. Integration points

---

## Acceptance Criteria

### What Makes Implementation Complete?

**Complete Means**:
- ✅ All functional requirements implemented
- ✅ All scenarios passing (success + error)
- ✅ All constraints satisfied (namespace, build, legal)
- ✅ Traceability established (code → requirement)
- ✅ Tests pass
- ✅ Code reviewed

**Incomplete Means**:
- ❌ "Most requirements done"
- ❌ "Happy path works"
- ❌ "I'll add error handling later"
- ❌ "Tests skip error scenarios"
- ❌ "Namespace not verified"

### Example Checklist

**Requirement**: Namespace Isolation

**Acceptance Criteria**:
- [ ] Public APIs use lui_ prefix
- [ ] Internal widgets use luixml_ prefix
- [ ] No lv_xml_ symbols (verified with grep)
- [ ] Namespace isolation tests pass

---

## Common Pitfalls

### Pitfall 1: Shallow Reading

**Problem**: Skimming the spec, missing details

**Symptoms**:
- Miss error scenarios
- Miss constraints
- Misunderstand requirements

**Solution**:
- Read the spec completely before starting
- Take notes on each requirement
- Verify understanding with scenarios

### Pitfall 2: Ignoring Namespace Constraints

**Problem**: "I'll fix namespace later"

**Symptoms**:
- lv_xml_ symbols in code
- Inconsistent prefixes
- Symbol collision risk

**Solution**:
- Design for namespace from start
- Verify with grep continuously
- Fix violations immediately

### Pitfall 3: Incomplete Error Handling

**Problem**: "I'll handle errors at the end"

**Symptoms**:
- Error cases untested
- Error codes don't match spec
- Recovery mechanisms missing

**Solution**:
- Implement error scenarios alongside success
- Use spec-specified error codes
- Test error recovery

---

## Quick Reference

**Requirements Analysis Checklist**:
- [ ] Read full specification
- [ ] Extract functional requirements
- [ ] Extract namespace constraints
- [ ] Map scenarios to tests
- [ ] Identify acceptance criteria
- [ ] Plan implementation tasks
- [ ] Verify constraints are achievable

**The Golden Rule**:

> **"Understand the requirement completely before writing a single line of code."**

---

**Next**: Read `06-COMMON-PITFALLS.md` to learn about common implementation pitfalls.
