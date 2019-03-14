type converter = Js.t({
    .
    [@bs.meth] makeHtml: string => string,
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
    reducer: (_action: action, _state) => { ReasonReact.NoUpdate },
    render: self => {
        switch(self.state.converter^) {
            | None            => <div></div>
            | Some(converter) => 
                <div dangerouslySetInnerHTML={{ "__html": converter##makeHtml(markdown) }} />
        }
    }
};