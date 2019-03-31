type state = {
    currentSlide: int,
    currentSlideContent: int,
    keyDownHandler: ref(Dom.keyboardEvent => unit),
};

type action =
  | PreviousSlide
  | NextSlide
  | GoToSlide(int, int)
;

let updateHistory = (slide, content) => {
  let newUrl = "#/" ++ string_of_int(slide) ++ "/" ++ string_of_int(content);
  HistoryRe.pushState(HistoryRe.state(DomRe.history), "", newUrl, DomRe.history);
}

let component = ReasonReact.reducerComponent("Slides");

let style = ReactDOMRe.Style.make(
    ~width="100%",
    ~height="100%",
    ~position="relative",
    ~overflow="hidden",
    ~backgroundColor="#002b36",
    ()
);

let controlsStyle = ReactDOMRe.Style.make(
    ~position="fixed",
    ~right="10px",
    ~bottom="20px",
    ()
);

let leftControlStyle = ReactDOMRe.Style.make(
    ~borderRightColor="#93a1a1",
    ~borderRightWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);
let rightControlStyle = ReactDOMRe.Style.make(
    ~borderLeftColor="#93a1a1",
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
        | "ArrowLeft" | "PageUp" => self.send(PreviousSlide)
        | "ArrowRight" | "PageDown" => self.send(NextSlide)
        | _ => ()
      });
    EventTargetRe.addKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );
    let pathSegments = Js.String.split("/", LocationRe.hash(DomRe.location));
    switch (pathSegments) {
      | [|"#", a, b|] => self.send(GoToSlide(int_of_string(a), int_of_string(b)))
      | _ => ()
    };
  },

  willUnmount: self => {
    EventTargetRe.removeKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );
  },

  reducer: (action, state) =>
    switch (action) {
    | PreviousSlide => {
        let lastContentOnPreviousSlide = state.currentSlide > 0
          ? List.length(List.nth(content, state.currentSlide-1)) - 1
          : -1 ;
        ReasonReact.UpdateWithSideEffects({
          ...state,
          currentSlide: max(state.currentSlideContent <= 0
            ? state.currentSlide - 1
            : state.currentSlide, 0),
          currentSlideContent: state.currentSlideContent <= 0
                                && state.currentSlide <= 0
                                ? 0
                                : max(state.currentSlideContent <= 0
                                    ? lastContentOnPreviousSlide
                                    : state.currentSlideContent - 1, 0),
        }, ({ state }) => updateHistory(state.currentSlide, state.currentSlideContent));
      }
    | NextSlide => {
        let lastContentOnThisSlide = List.length(List.nth(content, state.currentSlide)) - 1;
        let lastSlide = List.length(content) - 1;
        ReasonReact.UpdateWithSideEffects({
          ...state,
          currentSlide: min(state.currentSlideContent >= lastContentOnThisSlide
            ? state.currentSlide + 1
            : state.currentSlide, lastSlide),
          currentSlideContent: state.currentSlide == lastSlide
                                && state.currentSlideContent == lastContentOnThisSlide
                                ? state.currentSlideContent
                                : min(state.currentSlideContent >= lastContentOnThisSlide
                                    ? 0
                                    : state.currentSlideContent + 1, lastContentOnThisSlide),
        }, ({ state }) => updateHistory(state.currentSlide, state.currentSlideContent));
      }
    | GoToSlide(a, b) => ReasonReact.Update({
          ...state,
          currentSlide: a,
          currentSlideContent: b,
        });
    },

  render: self => {
    switch (isLoading) {
      | true => <h1>{ReasonReact.string("Loading slides...")}</h1>
      | false => {
          let slideContents: list(string) = 
            List.nth(content, self.state.currentSlide);
          <div style>
            <Slide content={slideContents} currentContentIndex={self.state.currentSlideContent} />
            <aside style={controlsStyle}>
              <button onClick={_event => self.send(PreviousSlide)} style={leftControlStyle}></button>
              <button onClick={_event => self.send(NextSlide)} style={rightControlStyle}></button>
            </aside>
          </div>;
        }
    }
  },
};
