# AM64x Project Setup From Scratch (Command Reference)

This is the full command path used to reach the current state: local repo initialized, baseline platform setup complete, GitHub remote configured, and `main` pushed.

## 1) Create the project structure

```bash
mkdir -p /Users/sam/am64x-industrial-automation/{firmware/{zephyr,mcux,boards,drivers,app},linux-apps/{services,scripts},platform/{am64x/{device-tree,configs,boot}},tools/{flash,debug,factory,ci},tests/{unit,integration,hil},docs/{architecture,interfaces,safety,runbooks},.github/workflows}
```

## 2) If needed, fix malformed `platform/` folders from shell brace expansion issues

```bash
mkdir -p /Users/sam/am64x-industrial-automation/platform/am64x/{device-tree,configs,boot} && rm -rf "/Users/sam/am64x-industrial-automation/platform/{am64x" "/Users/sam/am64x-industrial-automation/platform/{am64x/boot}" "/Users/sam/am64x-industrial-automation/platform/{am64x/configs}" "/Users/sam/am64x-industrial-automation/platform/{am64x/device-tree}"
```

## 3) Initialize git and commit scaffold/config files

```bash
git -C /Users/sam/am64x-industrial-automation init -b main
git -C /Users/sam/am64x-industrial-automation add .
git -C /Users/sam/am64x-industrial-automation commit -m "Initialize AM64x embedded project scaffold, CI, lint config, and Zephyr sample app" -m "Co-Authored-By: Oz <oz-agent@warp.dev>"
```

## 4) Install GitHub CLI

```bash
brew install gh
```

## 5) Authenticate GitHub CLI (you ran this successfully)

```bash
gh auth login
```

## 6) Create remote and push (attempted create + fallback to existing repo)

The first repo-create attempt failed because the name already existed:

```bash
gh repo create am64x-industrial-automation --source /Users/sam/am64x-industrial-automation --remote origin --private --push
```

So the working path was:

```bash
git -C /Users/sam/am64x-industrial-automation remote remove origin 2>/dev/null || true
git -C /Users/sam/am64x-industrial-automation remote add origin git@github.com:am64x-forge/am64x-industrial-automation.git
git -C /Users/sam/am64x-industrial-automation push -u origin main
```

## 7) Useful verification commands

```bash
git -C /Users/sam/am64x-industrial-automation --no-pager status --short --branch
git -C /Users/sam/am64x-industrial-automation --no-pager remote -v
git -C /Users/sam/am64x-industrial-automation --no-pager log --oneline -n 1
find /Users/sam/am64x-industrial-automation -type d | sort
```

## 8) Current expected state

- Local branch: `main`
- Tracking: `main...origin/main`
- Remote: `git@github.com:am64x-forge/am64x-industrial-automation.git`
- Initial commit: `ed2562a`

## 9) Additional commands used afterward (to version this runbook)

These were used when this runbook itself was added and pushed:

```bash
git -C /Users/sam/am64x-industrial-automation --no-pager status --short --branch
git -C /Users/sam/am64x-industrial-automation add docs/runbooks/setup-from-scratch.md
git -C /Users/sam/am64x-industrial-automation commit -m "Add setup-from-scratch command runbook" -m "Co-Authored-By: Oz <oz-agent@warp.dev>"
git -C /Users/sam/am64x-industrial-automation push -u origin main
```

Resulting follow-up commit:
- `d3025ad` (`Add setup-from-scratch command runbook`)

