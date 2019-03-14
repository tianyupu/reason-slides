let component = ReasonReact.statelessComponent("Slide");

let style = ReactDOMRe.Style.make(
    ~width="800px",
    ~height="450px",
    ~backgroundColor="#cccccc",
    ()
);

let make = (~content: list(string), ~currentContentIndex: int, _children) => {
    ...component,
    render: _self => {
        let slides = List.mapi((i, s) => i <= currentContentIndex ? <Markdown markdown={s} /> : <p></p>, content);
        <div style>
            {ReasonReact.array(Array.of_list(slides))}
        </div>;
    }
};