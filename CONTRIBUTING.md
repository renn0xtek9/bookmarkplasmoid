# CONTRIBUTING

We recommand the usage of the devcontainer with VSCode. This shall provide you with an environment that has all required dependencies.

Please use pre-commit to format all the files of the repo on every commit

```bash
pre-commit install
```

## How to

- Clean the repository

```bash
git clean -e ".vscode/*" -fxfd
```

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


## TODO 
- Fix this test: XbelParserTest::test_single_bookmark_in_complete_file() it is a test where a complete xml file is read that contains a single bookmark.
It does not pass and has result subsequent module are failing. Attention, may be the expected value is wrong (since we call read with invisilbe root item), maybe we shall not expect the first elment to be the bookmark itself, but instead it shall be the child
