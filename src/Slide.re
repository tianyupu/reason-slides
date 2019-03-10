let component = ReasonReact.statelessComponent("Slide");

let style = ReactDOMRe.Style.make(
    ~width="100vw",
    ~height="100vh",
    ~backgroundColor="#cccccc",
    ()
);

let make = (~text, _children) => {
    ...component,
    render: _self =>
    <div style>
        {ReasonReact.string(text)}
    </div>
}