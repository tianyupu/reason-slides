# The Reason for ReasonML
## Tianyu Pu
<div style="margin: auto; height: 50%; width: 50%">
    <img src="img/codemotion_logo_orange_white.png" />
    <img src="img/license-cc.png" />
    <img src="img/license-by.png" />
    <img src="img/license-nc.png" />
    <img src="img/license-sa.png" />
</div>
---

---
```nohighlight
Cannot read property '____' of undefined
```
---
![this is fine, really](img/this-is-fine.jpg)
---
(logos of various libraries designed to make JS less hard)
---
![reason](img/reason.svg)
---
![ocaml](img/ocaml.svg)
---
## 🚀 A whirlwind tour of ReasonML 🚀
---
### Types

100% coverage

Sound

Inferred
---
### Types in action

```reasonml
type name = string;
```

```reasonml
let firstName: name = "Tian";
```

---
### Variants

```reasonml
type loginStatus = 
  | NotLoggedIn
  | LoggedIn(string)
```

---
### Pattern matching (1)

```reasonml
let status = LoggedIn("tian");
…
…
…
…
…
```

---

### Pattern matching (1)

```reasonml
let status = LoggedIn("tian");
switch (status) {
  …
  …
  …
}
```

---

### Pattern matching (1)

```reasonml
let status = LoggedIn("tian");
switch (status) {
  | NotLoggedIn => ":("
  | …
  | …
}
```

---

### Pattern matching (1)

```reasonml
let status = LoggedIn("tian");
switch (status) {
  | NotLoggedIn => ":("
  | LoggedIn("admin") => "!"
  | …
}
```

---

### Pattern matching (1)

```reasonml
let status = LoggedIn("tian");
switch (status) {
  | NotLoggedIn => ":("
  | LoggedIn("admin") => "!"
  | LoggedIn(user) => ":)"
}
```

---
### Pattern matching (2)

```reasonml
switch (someList) {
  …
  …
  …
}
```

---

### Pattern matching (2)

```reasonml
switch (someList) {
  | [] => "The list is empty..."
  …
  …
}
```

---

### Pattern matching (2)

```reasonml
switch (someList) {
  | [] => "The list is empty..."
  | [head, ...tail] => …
  …
}
```

---

### Pattern matching (2)

```reasonml
switch (someList) {
  | [] => "The list is empty..."
  | [head, ...tail] => head ++
    " is the first item"
}
```

---
### Pattern matching (3)

```reasonml
switch (divisibleBy3, divisibleBy5) {
  | (true, true) => "Fizz Buzz"
  | (true, false) => "Fizz"
  | (false, true) => "Buzz"
  | (false, false) => ""
}
```

---
### Special mention: `option`

```reasonml
type option('t) = 
  | Some('t)
  | None
```

---
No more null / undefined bugs, ever! 🙌
---
### Tuples

```reasonml
(1, "H", 1.008)
(2, "He", 4.0026)
```

---
### Records

```reasonml
type conference = {
  …
  …
  …
};
```

---

### Records

```reasonml
type conference = {
  name: string,
  year: int,
  location: string
};
```

---
### Records

```reasonml
let thisConference = {
  … 
  … 
  … 
};
```

---

### Records

```reasonml
let thisConference = {
  name: "Codemotion",
  year: 2019,
  location: "AMS"
};
```

---
### Objects - closed

```reasonml
type person = {
  …
  …
};
```

---

### Objects - closed

```reasonml
type person = {
  …
  name: string
};
```

---

### Objects - closed

```reasonml
type person = {
  .
  name: string
};
```

---

### Objects - closed

```reasonml
let author: person = {
  …
  …
};
```

```reasonml
…
```

---

### Objects - closed 

```reasonml
let author: person = {
  val age = 100;
  …
};
```

```reasonml
…
```

---

### Objects - closed 

```reasonml
let author: person = {
  val age = 100;
  pub name = "V. Hugo";
};
```

```reasonml
…
```

---

### Objects - closed 

```reasonml
let author: person = {
  val age = 100;
  pub name = "V. Hugo";
};
```

```reasonml
author#name
```

---
### Objects - open

```reasonml
type named('t) = {
  ..
  name: string
} as 't;
```

---
### Objects - open

```reasonml
let author: named({. name: string, write: string => unit}) = {
  val currentBook = ref(string);
  pub name = "Victor Hugo";
  pub write = string => currentBook := currentBook^ ++ string
};
```

---
### Immutability (1)

```reasonml
let meaningOfLife = 42;
let meaningOfLife = 9001;
```

---
### Immutability (2)

```reasonml
let meaningOfLife = ref(42);
meaningOfLife := 9001;
```

---
### Modules

Every .re file is a module

No need to import modules
---
Directory structure changes? Easy!
---
### `external`

```reasonml
external cStrcmp: string => int = "strcmp";
```

---
### _Reason #1:_

The language! ✨
---
## But, JavaScript?!?!

---
ReasonML != JavaScript
---
ReasonML == OCaml
---
OCaml → native code
---
OCaml → JavaScript!
---
How? 🤔
---
<img width="150px"
     src="img/bucklescript.svg"
     alt="BuckleScript logo" />
---
### BuckleScript

1 Reason file → 1 JS file

Use the JS files as normal
---
All you need: **bsconfig.json** and **`bsb`**
---
#### Minimal bsconfig.json

```json
{
  "name": "my-project",
  "sources": {
    "dir": "src"
  }
}
```

---
#### `bsb`

```nohighlight
npm install -g bs-platform
```

```nohighlight
bsb -make-world [-w]
```

---
(example of compiled JS)
---
TLDR; You can already write entire JS apps in pure Reason! 🎉
---
### Using JS libraries in Reason
---
Remember `external`?
---
```reasonml
external cStrcmp: string => int = "strcmp";
```

```reasonml
[@bs.val] btoa: string => string = "btoa";
```

```reasonml
let encodedData = btoa("Hi, Codemotion!");
```

---
But first, check for existing bindings!
---
![redex.github.io](img/redex.png)
---
Add it to `bs-dependencies` in bsconfig.json:

```json
{
  "name": "my-project",
  "sources": {
    "dir": "src"
  },
  "bs-dependencies": [
    "bs-webapi"
  ]
}
```

---
Otherwise, write your own:
(examples)
---
### Using Reason in JS
---

Again, the bsconfig.json:

```json
{
  "name": "my-project",
  "sources": { "dir": "src" },
  "bs-dependencies": [ "bs-webapi" ],
  …
  …
  …
  …
  …
}
```

---

Again, the bsconfig.json:

```json
{
  "name": "my-project",
  "sources": { "dir": "src" },
  "bs-dependencies": [ "bs-webapi" ],
  "package-specs": [{
    "module": "commonjs",
    …
  }],
  …
}
```

---

Again, the bsconfig.json:

```json
{
  "name": "my-project",
  "sources": { "dir": "src" },
  "bs-dependencies": [ "bs-webapi" ],
  "package-specs": [{
    "module": "commonjs",
    "in-source": true
  }],
  …
}
```

---

Again, the bsconfig.json:

```json
{
  "name": "my-project",
  "sources": { "dir": "src" },
  "bs-dependencies": [ "bs-webapi" ],
  "package-specs": [{
    "module": "commonjs",
    "in-source": true
  }],
  "suffix": ".bs.js"
}
```

---
#### Supported module types

```nohighlight
amdjs[-global]
commonjs
es6[-global]
```

---
(Migrating an existing file into Reason - the process)
---
### _Reason #2:_

Smooth JS interop, thanks to BuckleScript!
---
## Questions?

---
## Recap

---
## The end

---
## The ~~end~~ beginning

---
## Thank you!
[linkedin.com/in/tianyupu](https://www.linkedin.com/in/tianyupu/)
---
## Resources
[bs directives reference](https://github.com/moroshko/bs-blabla)
[bsconfig schema reference](https://bucklescript.github.io/bucklescript/docson/#build-schema.json)