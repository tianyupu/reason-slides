type converter = Js.t({
    .
    [@bs.meth] makeHtml: string => string,
    [@bs.meth] setFlavor: string => unit,
});
[@bs.new] [@bs.module "showdown"] external showdownConverter: converter = "Converter";

type state = {
    converter: ref(option(converter)),
};
type action;
let component = ReasonReact.reducerComponent("Markdown");
let make = (~markdown, _children) => {
    ...component,
    initialState: () => {
        converter: ref(Some(showdownConverter)),
    },
    didMount: self => {
        switch(self.state.converter^) {
            | None            => ()
            | Some(converter) => converter##setFlavor("github")
        }
    },
    reducer: (_action: action, _state) => { ReasonReact.NoUpdate },
    render: self => {
        switch(self.state.converter^) {
            | None            => ReasonReact.null
            | Some(converter) => 
                <div dangerouslySetInnerHTML={{ "__html": converter##makeHtml(markdown) }} />
        }
    }
};