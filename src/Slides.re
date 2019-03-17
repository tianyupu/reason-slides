type state = {
    currentSlide: int,
    currentSlideContent: int,
    keyDownHandler: ref(Dom.keyboardEvent => unit),
};

type action =
  | PreviousSlide
  | NextSlide
;

let component = ReasonReact.reducerComponent("Slides");

let style = ReactDOMRe.Style.make(
    ~width="100%",
    ~height="100%",
    ~position="relative",
    ~overflow="hidden",
    ~backgroundColor="#eba6f4",
    ()
);

let controlsStyle = ReactDOMRe.Style.make(
    ~position="fixed",
    ~right="10px",
    ~bottom="20px",
    ()
);

let leftControlStyle = ReactDOMRe.Style.make(
    ~borderRightColor="#777",
    ~borderRightWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);
let rightControlStyle = ReactDOMRe.Style.make(
    ~borderLeftColor="#777",
    ~borderLeftWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);

let make = (~content, ~isLoading, _children) => {
  ...component,

  initialState: () => { 
    currentSlide: 0,
    currentSlideContent: 0,
    keyDownHandler: ref(_e => ()),
  },

  didMount: self => {
    self.state.keyDownHandler := e => (switch (KeyboardEventRe.key(e)) {
        | "ArrowLeft" => self.send(PreviousSlide)
        | "ArrowRight" => self.send(NextSlide)
        | _ => ()
      });
    EventTargetRe.addKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );
  },

  willUnmount: self => {
    EventTargetRe.removeKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );
  },

  reducer: (action, state) =>
    switch (action) {
    | PreviousSlide => ReasonReact.Update({
        ...state,
        currentSlide: max(state.currentSlideContent <= 0
          ? state.currentSlide - 1
          : state.currentSlide, 0),
        currentSlideContent: max(state.currentSlideContent <= 0
          ? 0
          : state.currentSlideContent - 1, 0),
      })
    | NextSlide => ReasonReact.Update({
        ...state,
        currentSlide: min(state.currentSlideContent >= List.length(List.nth(content, state.currentSlide)) - 1
          ? state.currentSlide + 1
          : state.currentSlide, List.length(content) - 1),
        currentSlideContent: state.currentSlide == List.length(content) - 1
                              && state.currentSlideContent == List.length(List.nth(content, state.currentSlide)) - 1
                              ? state.currentSlideContent
                              : min(state.currentSlideContent >= List.length(List.nth(content, state.currentSlide)) - 1
                                ? 0
                                : state.currentSlideContent + 1, List.length(List.nth(content, state.currentSlide)) - 1),
        })
      },

  render: self => {
    let slideContents: list(string) = 
      List.nth(content, self.state.currentSlide);
    isLoading
    ? <h1>{ReasonReact.string("Loading slides...")}</h1>
    : <div style>
        <Slide content={slideContents} currentContentIndex={self.state.currentSlideContent} />
        <aside style={controlsStyle}>
          <button onClick={_event => self.send(PreviousSlide)} style={leftControlStyle}></button>
          <button onClick={_event => self.send(NextSlide)} style={rightControlStyle}></button>
        </aside>
      </div>;
  },
};
