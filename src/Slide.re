let component = ReasonReact.statelessComponent("Slide");

let style = ReactDOMRe.Style.make(
    ~width="90%",
    ~height="90%",
    ~margin="auto",
    ~textAlign="center",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="center",
    ~left="50%",
    ~top="50%",
    ~transform="translate(-50%, -50%)",
    ~position="absolute",
    ()
);

let contentStyle = (~isHidden) => ReactDOMRe.Style.make(
    ~visibility={isHidden ? "hidden" : "visible"},
    ~display="flex",
    ~justifyContent="center",
    ~alignItems="center",
    ()
);

let make = (~content: list(string), ~currentContentIndex: int, _children) => {
    ...component,
    render: _self => {
        let slides = 
            List.mapi((i, s) => 
                <div style={contentStyle(~isHidden={i > currentContentIndex})}><Markdown markdown={s} /></div>
            , content);
        <div style className="slide-container">
            {ReasonReact.array(Array.of_list(slides))}
        </div>;
    }
};