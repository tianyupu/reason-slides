type state = {
    currentSlide: int,
    currentSlideContent: int,
};

type action =
  | PreviousSlide
  | NextSlide
;

let component = ReasonReact.reducerComponent("Slides");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~content, ~isLoading, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => { 
    currentSlide: 0,
    currentSlideContent: 0,
  },

  reducer: (action, state) =>
    switch (action) {
    | PreviousSlide => ReasonReact.Update({
        currentSlide: max(state.currentSlideContent <= 0
          ? state.currentSlide - 1
          : state.currentSlide, 0),
        currentSlideContent: max(state.currentSlideContent <= 0
          ? 0
          : state.currentSlideContent - 1, 0),
      })
    | NextSlide => ReasonReact.Update({
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
    : <div>
        <Slide content={slideContents} currentContentIndex={self.state.currentSlideContent} />
        <button onClick={_event => self.send(PreviousSlide)}>
          {ReasonReact.string("<")}
        </button>
        <button onClick={_event => self.send(NextSlide)}>
          {ReasonReact.string(">")}
        </button>
      </div>;
  },
};
