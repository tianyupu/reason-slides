let component = ReasonReact.statelessComponent("SlideControls");

let controlsStyle = ReactDOMRe.Style.make(
    ~position="fixed",
    ~right="10px",
    ~bottom="20px",
    ()
);

let leftControlStyle = controlsColor => ReactDOMRe.Style.make(
    ~borderRightColor=controlsColor,
    ~borderRightWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);
let rightControlStyle = controlsColor => ReactDOMRe.Style.make(
    ~borderLeftColor=controlsColor,
    ~borderLeftWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);

let make = (~controlsColor, ~prevCallback, ~nextCallback, _children) => {
    ...component,
    render: _self => {
      <aside style=controlsStyle>
        <button
          onClick={_event => prevCallback()}
          style={leftControlStyle(controlsColor)}
        />
        <button
          onClick={_event => nextCallback()}
          style={rightControlStyle(controlsColor)}
        />
      </aside>;
    }
};