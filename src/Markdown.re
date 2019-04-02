[@bs.module "tianyupu-highlight.js"] external highlightBlock: Dom.element => unit = "highlightBlock";

type converter = Js.t({
    .
    [@bs.meth] makeHtml: string => string,
    [@bs.meth] setFlavor: string => unit,
});
[@bs.new] [@bs.module "showdown"] external showdownConverter: converter = "Converter";

type state = {
    converter: ref(option(converter)),
    markdownRef: ref(option(Dom.element)),
};
type action;

let setMarkdownRef = (theRef, { ReasonReact.state }) => {
    state.markdownRef := switch (Js.Nullable.toOption(theRef)) {
        | None => None
        | Some(el) => ElementRe.querySelector("pre code", el)
    }
};

let component = ReasonReact.reducerComponent("Markdown");
let make = (~markdown, _children) => {
    ...component,
    initialState: () => {
        converter: ref(Some(showdownConverter)),
        markdownRef: ref(None),
    },
    didMount: self => {
        switch(self.state.converter^) {
            | None            => ()
            | Some(converter) => converter##setFlavor("github")
        }
        switch (self.state.markdownRef^) {
            | None      => ()
            | Some(el)  => highlightBlock(el)
        }
    },
    didUpdate: oldAndNewSelf => {
        switch (oldAndNewSelf.newSelf.state.markdownRef^) {
            | None      => ()
            | Some(el)  => highlightBlock(el)
        }
    },
    reducer: (_action: action, _state) => { ReasonReact.NoUpdate },
    render: self => {
        switch(self.state.converter^) {
            | None            => ReasonReact.null
            | Some(converter) => 
                <div ref={self.handle(setMarkdownRef)}
                     dangerouslySetInnerHTML={{ "__html": converter##makeHtml(markdown) }} />
        }
    }
};