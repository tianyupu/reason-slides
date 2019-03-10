type state = {
    currentSlide: int,
};

type action =
  | PreviousSlide
  | NextSlide
;

let component = ReasonReact.reducerComponent("Slides");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~content, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => { currentSlide: 0, },

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | PreviousSlide => ReasonReact.Update({currentSlide: state.currentSlide - 1})
    | NextSlide => ReasonReact.Update({currentSlide: state.currentSlide + 1})
    },

  render: self => {
    let message =
      List.nth(content, self.state.currentSlide);
    <div>
      {ReasonReact.string(message)}
      <button onClick={_event => self.send(PreviousSlide)}>
        {ReasonReact.string("<")}
      </button>
      <button onClick={_event => self.send(NextSlide)}>
        {ReasonReact.string(">")}
      </button>
    </div>;
  },
};
