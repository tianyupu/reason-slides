let component = ReasonReact.statelessComponent("Slide");

let style = ReactDOMRe.Style.make(
    ~width="90%",
    ~height="90%",
    ~margin="auto",
    ~textAlign="center",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="center",
    ()
);

let make = (~content: list(string), ~currentContentIndex: int, _children) => {
    ...component,
    render: _self => {
        let slides = List.mapi((i, s) => i <= currentContentIndex ? <Markdown markdown={s} /> : ReasonReact.null, content);
        <div style>
            {ReasonReact.array(Array.of_list(slides))}
        </div>;
    }
};