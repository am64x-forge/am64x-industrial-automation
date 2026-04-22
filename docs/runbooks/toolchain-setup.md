# Toolchain Setup Runbook (AM64x + Zephyr + Linux)
This runbook defines a reproducible setup for host tools, Zephyr workflows, and TI AM64x SDK workflows.

## 1) Host Prerequisites
Install baseline tooling:
- Git, Python 3.11+, pip, virtualenv/venv
- CMake, Ninja, GCC/Clang toolchains
- clang-format, clang-tidy, cppcheck
- OpenOCD, GDB, and serial console tools

Recommended package groups:
- Build: `cmake`, `ninja`, `make`, compiler toolchains
- Analysis: `clang-format`, `clang-tidy`, `cppcheck`
- Python: `python3`, `python3-venv`, `pipx`
- Debug/flash: `openocd`, `gdb-multiarch`, `picocom` (or equivalent)

## 2) Repository Bootstrap
From repository root:
1. Create Python virtual environment for project tooling.
2. Activate the virtual environment.
3. Install Python development dependencies.

Example:
```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip
pip install west ruff mypy
```

## 3) Zephyr Workspace Setup
Use west to manage Zephyr components.

If this repository becomes a Zephyr workspace:
1. Ensure a valid `west.yml` exists.
2. Initialize and update modules.
3. Export Zephyr CMake package metadata.

Example:
```bash
west init -l firmware/zephyr
west update
west zephyr-export
```

Toolchain notes:
- Prefer Zephyr SDK for consistency in CI and local builds.
- Pin Zephyr and module revisions in `west.yml`.
- Keep board overlays in `firmware/boards/`.

## 4) TI AM64x SDK Setup Strategy
AM64x work typically spans:
- Linux domain (A53): Processor SDK Linux
- MCU/RT domain (R5F): MCU+ SDK

Recommended approach:
1. Install TI SDKs under a versioned path outside the repo.
2. Record exact versions in `docs/runbooks/` and CI variables.
3. Keep project-specific scripts in `tools/` that consume SDK paths via environment variables.

Required environment variables (example names):
- `TI_PSDK_LINUX_PATH`
- `TI_MCU_PLUS_SDK_PATH`
- `ZEPHYR_SDK_INSTALL_DIR`

Do not hardcode local absolute SDK paths in committed scripts.

## 5) Local Validation Commands
Run these from repo root before pushing changes:

```bash
ruff check linux-apps tools tests
mypy linux-apps tools tests
```

When C/C++ source exists:
```bash
find firmware linux-apps platform tests tools -type f \( -name "*.c" -o -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print0 | xargs -0 -n1 clang-format --dry-run --Werror
cppcheck --enable=warning,style,performance,portability --error-exitcode=1 firmware linux-apps platform tests tools
```

When Zephyr targets are available:
```bash
west build -b <board_name> <zephyr_app_path>
west build -t run
```

## 6) CI Alignment
The CI workflow in `.github/workflows/ci.yml` is intentionally conservative:
- It skips checks when matching files are not present.
- It provides fast feedback for lint/static analysis and basic build smoke checks.

As the project grows:
1. Add board-specific Zephyr build jobs.
2. Add TI SDK containerized jobs (self-hosted or managed runner).
3. Add HIL jobs for hardware validation in `tests/hil/`.

## 7) Troubleshooting
- `west` command not found: activate `.venv` and verify `pip install west`.
- Zephyr package resolution issues: rerun `west zephyr-export`.
- Toolchain mismatch errors: verify SDK versions and exported environment variables.
- Inconsistent formatting locally vs CI: ensure same `clang-format` major version.
