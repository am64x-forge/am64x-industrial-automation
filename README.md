# AM64x Industrial Automation Project
This repository is a starter structure for embedded development targeting the TI AM64x SoC across Linux user space, MCU/RT cores, and Zephyr-based firmware components.

## Project Structure
```
am64x-industrial-automation/
├── firmware/
│   ├── zephyr/                # Zephyr workspace/modules and app code
│   ├── mcux/                  # TI MCU+ SDK based components (R5F/MCU domains)
│   ├── boards/                # Board-specific definitions and overlays
│   ├── drivers/               # Reusable hardware drivers
│   └── app/                   # Product-specific firmware logic
├── linux-apps/
│   ├── services/              # Linux-side daemons/apps (C++/Python)
│   └── scripts/               # Operational/support scripts
├── platform/
│   └── am64x/
│       ├── device-tree/       # DTS overlays/fragments
│       ├── configs/           # Boot/runtime configuration
│       └── boot/              # Boot-flow assets and notes
├── tools/
│   ├── flash/                 # Flashing utilities and wrappers
│   ├── debug/                 # Debug helpers (GDB/OpenOCD/serial)
│   ├── factory/               # Manufacturing/provisioning tools
│   └── ci/                    # CI helper scripts
├── tests/
│   ├── unit/                  # Host-side unit tests
│   ├── integration/           # Cross-component integration tests
│   └── hil/                   # Hardware-in-the-loop tests
├── docs/
│   ├── architecture/          # System design docs
│   ├── interfaces/            # Interface contracts and protocols
│   ├── safety/                # Safety assumptions and hazard notes
│   └── runbooks/              # Operations and troubleshooting runbooks
└── .github/
    └── workflows/             # CI pipelines
```

## Branching and Delivery Workflow
1. Create short-lived feature branches from `main`.
2. Keep commits small and scoped (one concern per commit).
3. Open a PR early; iterate with CI and review feedback.
4. Merge only when all required checks pass.

Suggested branch naming:
- `feature/<topic>`
- `fix/<topic>`
- `chore/<topic>`

## Development Workflow (Warp/Oz-Centered)
1. Define task and acceptance criteria in `docs/runbooks/` or PR description.
2. Ask Oz in Warp to generate an implementation plan and checkpoints.
3. Implement changes in small steps.
4. Use Oz to run verification loops and summarize failures.
5. Use Oz to prepare PR summaries and risk notes.

Recommended daily loop:
1. `git pull --rebase`
2. Implement targeted change
3. Build + test locally
4. Run static checks
5. Commit with clear message
6. Push and open/update PR

## Build and Validation Gates
Every PR should satisfy:
- Build success for affected firmware and Linux components
- Unit/integration tests passing
- Static analysis clean (or justified deviations)
- Formatting/lint checks passing

Typical check categories:
- C/C++: formatting, warnings-as-errors policy, static analysis
- Python: formatting/lint/type checks for scripts/services
- Zephyr: west build/test steps for targeted boards

## Tooling Baseline
- Git + GitHub for source control and collaboration
- CMake + Ninja for native builds where applicable
- Zephyr `west` tooling for Zephyr components
- Python virtual environments for Python tools/scripts
- CI workflows in `.github/workflows/` for automated checks

## CI/CD Expectations
Create workflows for:
1. Pull request verification:
   - Build
   - Unit tests
   - Lint/static analysis
2. Main branch:
   - Reproducible release artifacts
   - Versioned outputs and changelog notes
3. Optional nightly:
   - Extended integration/HIL test suites

## Documentation Rules
- Update architecture/interface docs for any behavior change.
- Document hardware assumptions near the code and in `docs/safety/`.
- Add troubleshooting steps to `docs/runbooks/` when fixing field-like issues.

## First Next Steps
1. Initialize git and push repository to GitHub.
2. Add initial CI workflow in `.github/workflows/ci.yml`.
3. Add coding standards (`.clang-format`, Python lint config, commit conventions).
4. Add Zephyr and TI SDK setup guides under `docs/runbooks/`.
