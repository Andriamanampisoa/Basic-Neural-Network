# Contributing

This document outlines the guidelines and workflows we follow to ensure a clear and effective development process.

## Development Strategy

We use **Trunk-Based Development** with Git and GitHub. All development work is done in short-lived branches created from the main branch (`main`).

📌 **Do not work on a branch after it has been merged and deleted.**

## Branching

### Naming Convention

Branch names should follow the format:

```
<github-ticket-id>-<nature>-<description>
```

- `github-ticket-id` (optional): ID of the corresponding GitHub ticket (e.g. `abc123de`)
- `nature`: Type of work (e.g. `feature`, `bugfix`, `refactor`, `chore`)
- `description`: Brief purpose of the branch, in kebab-case

**Examples:**

- `ID-9-feature-passport-auth`
- `bugfix-security-breach-header`

### Creating a Branch

```bash
git checkout main
git pull origin main
git checkout -b ID-XX-feature-description
```

## Commit Messages

We follow the Conventional Commits spec with a few additions:

### Format

```
<type>(<optional-scope>): <description>
```

#### Types

- `feat`: New feature
- `anomaly`: Unexpected behavior that doesn’t break the app
- `bug`: Issue that breaks the app
- `refactor`: Code improvements without behavior changes
- `build`: Changes to build system/configuration
- `tests`: Adding or fixing tests
- `docs`: Documentation updates
- `chore`: Other changes not fitting above
- `ci`: Continuous integration changes

#### Guidelines

- Use **present** tense, imperative form (e.g., "add", not "added")
- Do not capitalize the first letter
- Do not end with a period
- Keep under 80 characters

#### Examples

- `feat(auth): add passport authentication`
- `fix(profile): correct display of user's full name`
- `refactor(database): improve user query performance`
- `docs: clarify installation instructions`

## Pull Requests (PRs)

### Creating a PR

1. Push commits on a new branch from main.
2. Open a PR using the following title format:

```
[github-project-ticket-id] short description
```

- `ticket-id`: optional ID of the corresponding GitHub project ticket (ex: `abc123de`)
- `short description`: related to the GitHub project ticket, no capitalization or period, present tense
