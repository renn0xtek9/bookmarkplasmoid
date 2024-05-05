# CONTRIBUTING 

We recommand the usage of the devcontainer with VSCode. This shall provide you with an environment that has all required dependencies.


Please use pre-commit to format all the files of the repo on every commit 

```bash 
pre-commit install 
```

## How to 
- Format all files:
```bash
pre-commit run --all-files
```
- Build
```bash 
./scripts/build.sh 
``` 
- Run tests 
```bash 
./scripts/test.sh
``` 
- Install locally 
```bash 
./scripts/install.sh 
```
