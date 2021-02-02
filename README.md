# dog

A naive clone of `cat`.

## Usage

To print out a file:

```bash
dog foo.c
```

To print out a file with line numbers:

```bash
dog -n foo.c
```

OR

```bash
dog --number foo.c
```

To print out multiple files:

```bash
dog foo.c bar.c fizz.py buzz.py
```

To print out from standard input:

```bash
dog
```

OR 

```bash
dog -
```

## Roadmap

- [x] Print one file
- [x] Print multiple files
- [x] Accept flag to show line numbers (`-n` or `--number`)
- [x] Print from standard input (i.e. `cat -`)
- [ ] Do not print file(s) when an invalid flag is given
- [ ] Throw an error when given a directory as an argument
- [ ] Fix standard error printing before previous file is done printing
    - When `dog dog.c bad` is run, for instance, the error for `dog: bad: No such file or directory`
    prints before `dog.c` is fully printed