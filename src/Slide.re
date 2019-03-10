let component = ReasonReact.statelessComponent("Slide");

let style = ReactDOMRe.Style.make(
    ~width="400px",
    ~height="300px",
    ~backgroundColor="#cccccc",
    ()
);

let make = (~content: list(string), ~currentContentIndex: int, _children) => {
    ...component,
    render: _self => {
        let slides = List.mapi((i, s) => i <= currentContentIndex ? <p>{ReasonReact.string(s)}</p> : <p></p>, content);
        <div style>
            {ReasonReact.array(Array.of_list(slides))}
        </div>;
    }
};