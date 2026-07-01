# Contributing to Borealis 

Thanks for checking this out! Just be aware this is currently a **solo project**. I may review contributions as time allows, but response times will vary significantly.

---

## Before you start

**Open an issue first.** If you're thinking about working on something, drop a note describing what you have in mind. 

---

## Code quality bar

I'm not at all strict about formatting tools or 100test coverage yet, but  aim for:

- **Readability**: Variable/function names make sense; _comments are important._
- **Basic Testing**: The engine should build cleanly and handle at least:
  - A full legal chess game start-to-finish
  - Loading positions via FEN strings
  - No obvious crashes on standard operation
  
Under no circumstances should you break existing functionality.

---

## AI usage

I am using Claude to a limited extent in this project. If you do the same, it's fine.

However, this is a project _run by humans and for humans_. 

Thus, do not:

- Spam the repo with PRs consisting of AI-generated code
- Make a PR with code that you don't understand
- Pretend that you wrote code that you didn't
- Simply copy-and-paste code from an LLM to here


---

## Making changes

1. Fork the repo
2. Create a branch with a descriptive name (e.g., `fix-en-passant-bug`)
3. Make changes, test locally
4. Submit a PR with context about what you changed and why

---

## License

By contributing, you agree your changes will be licensed under **GPLv3**. This means derivative works must stay open-source too. 

---

## Reality check

This is essentially one-person development right now. I appreciate PRs, but I can't promise fast turnaround. Some will sit for a while. I'll still try to get to them when possible unless explicitly closed.

Thanks for understanding and for taking interest anyway! Once the engine can handle UCI and all chess rules/edge cases, I'll be able to deal with PRs.

— Chestertonian

---

*July 2026*
