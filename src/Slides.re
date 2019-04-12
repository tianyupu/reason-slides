[%raw {| require("tianyupu-highlight.js/styles/solarized-dark.css") |}];
[%raw {| require("tianyupu-highlight.js/styles/solarized-light.css") |}];

type state = {
    currentSlide: int,
    currentSlideContent: int,
    keyDownHandler: ref(Dom.keyboardEvent => unit),
    isDarkMode: bool,
    lightStyleEl: ref(option(Dom.element)),
    darkStyleEl: ref(option(Dom.element)),
};

type action =
  | PreviousSlide
  | NextSlide
  | GoToSlide(int, int)
  | ToggleDarkMode
;

let updateOrReplaceHistory = (~replace, slide, content) => {
  let newUrl = "#/" ++ string_of_int(slide) ++ "/" ++ string_of_int(content);
  replace
    ? HistoryRe.replaceState(HistoryRe.state(DomRe.history), "", newUrl, DomRe.history)
    : HistoryRe.pushState(HistoryRe.state(DomRe.history), "", newUrl, DomRe.history);
}

let resetSlides = (state, slideIndex, slideContentIndex) => ReasonReact.UpdateWithSideEffects({
  ...state,
  currentSlide: slideIndex,
  currentSlideContent: slideContentIndex,
}, ({ state }) => updateOrReplaceHistory(~replace=true, state.currentSlide, state.currentSlideContent))

let component = ReasonReact.reducerComponent("Slides");

let backgroundColor = isDarkMode => isDarkMode ? "#002b36" : "#fdf6e3";
let contentColor = isDarkMode => isDarkMode ? "#839496" : "#657b83";

let style = isDarkMode => ReactDOMRe.Style.make(
    ~width="100%",
    ~height="100%",
    ~position="relative",
    ~overflow="hidden",
    ~backgroundColor=backgroundColor(isDarkMode),
    ~color=contentColor(isDarkMode),
    ()
);

let controlsStyle = ReactDOMRe.Style.make(
    ~position="fixed",
    ~right="10px",
    ~bottom="20px",
    ()
);

let leftControlStyle = isDarkMode => ReactDOMRe.Style.make(
    ~borderRightColor=contentColor(isDarkMode),
    ~borderRightWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);
let rightControlStyle = isDarkMode => ReactDOMRe.Style.make(
    ~borderLeftColor=contentColor(isDarkMode),
    ~borderLeftWidth="22px",
    ~padding="0",
    ~backgroundColor="transparent",
    ~border="12px solid transparent",
    ~cursor="pointer",
    ~margin="0 5px 0 5px",
    ()
);

let make = (~content, _children) => {
  ...component,

  initialState: () => { 
    currentSlide: 0,
    currentSlideContent: 0,
    keyDownHandler: ref(_e => ()),
    isDarkMode: true,
    lightStyleEl: ref(None),
    darkStyleEl: ref(None),
  },

  didMount: self => {
    self.state.keyDownHandler := e => switch (KeyboardEventRe.key(e)) {
        | "ArrowLeft" | "PageUp" => self.send(PreviousSlide)
        | "ArrowRight" | "PageDown" => self.send(NextSlide)
        | "f" => switch (DocumentRe.getElementById("index", Webapi.Dom.document)) {
          | Some(el) => el |> ElementRe.requestFullscreen
          | None => ()
        }
        | "c" => self.send(ToggleDarkMode)
        | _ => ()
      };
    EventTargetRe.addKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );

    let pathSegments = Js.String.split("/", LocationRe.hash(DomRe.location));
    switch (pathSegments) {
      | [|"#", a, b|] => self.send(GoToSlide(int_of_string(a), int_of_string(b)))
      | _ => self.send(GoToSlide(0, 0))
    };

    let lightEl = DocumentRe.getElementById("light", Webapi.Dom.document);
    let darkEl = DocumentRe.getElementById("dark", Webapi.Dom.document);
    switch (self.state.isDarkMode, lightEl, darkEl) {
      | (true, Some(light), Some(dark)) => {
        ElementRe.remove(light);
        self.state.lightStyleEl := Some(light);
        self.state.darkStyleEl := Some(dark);
      }
      | (false, Some(light), Some(dark)) => {
        ElementRe.remove(dark);
        self.state.lightStyleEl := Some(light);
        self.state.darkStyleEl := Some(dark);
      }
      | (_, _, _) => ()
    }
  },

  willUnmount: self => {
    EventTargetRe.removeKeyDownEventListener(
      self.state.keyDownHandler^,
      DocumentRe.asEventTarget(Webapi.Dom.document)
    );
  },

  didUpdate: ({ newSelf }) => {
    let lightEl = DocumentRe.getElementById("light", Webapi.Dom.document);
    let darkEl = DocumentRe.getElementById("dark", Webapi.Dom.document);
    let bodyEl = DocumentRe.querySelector("body", Webapi.Dom.document);
    switch (newSelf.state.isDarkMode, newSelf.state.lightStyleEl^, newSelf.state.darkStyleEl^, lightEl, darkEl, bodyEl) {
      | (true, _, Some(dark), None, None, Some(body)) => {
        ElementRe.appendChild(dark, body);
      }
      | (true, _, Some(_dark), None, Some(_currDark), _) => ()
      | (true, _, Some(dark), Some(currLight), None, Some(body)) => {
        ElementRe.remove(currLight);
        ElementRe.appendChild(dark, body);
      }
      | (true, _, Some(_dark), Some(currLight), Some(_currDark), _) => {
        ElementRe.remove(currLight);
      }
      | (false, Some(light), _, None, None, Some(body)) => {
        ElementRe.appendChild(light, body);
      }
      | (false, Some(_light), _, Some(_currLight), None, _) => ()
      | (false, Some(light), _, None, Some(currDark), Some(body)) => {
        ElementRe.remove(currDark);
        ElementRe.appendChild(light, body);
      }
      | (false, Some(_light), _, Some(_currLight), Some(currDark), _) => {
        ElementRe.remove(currDark);
      }
      | (_, _, _, _, _, _) => ()
    }
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
        }, ({ state }) => updateOrReplaceHistory(~replace=false, state.currentSlide, state.currentSlideContent));
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
        }, ({ state }) => updateOrReplaceHistory(~replace=false, state.currentSlide, state.currentSlideContent));
      }
    | GoToSlide(a, b) => {
      switch (List.nth(content, a)) {
        | slide => switch (List.nth(slide, b)) {
            | _content => resetSlides(state, a, b)
            | exception Failure("nth") => resetSlides(state, 0, 0)
          }
        | exception Failure("nth") => resetSlides(state, 0, 0)
        }
      }
    | ToggleDarkMode => ReasonReact.Update({ ...state, isDarkMode: !state.isDarkMode })
    },

  render: self => {
    let { isDarkMode } = self.state;
    let slideContents: list(string) = 
      List.nth(content, self.state.currentSlide);
    <div style={style(isDarkMode)}>
      <Slide content={slideContents} currentContentIndex={self.state.currentSlideContent} />
      <aside style={controlsStyle}>
        <button onClick={_event => self.send(PreviousSlide)} style={leftControlStyle(isDarkMode)}></button>
        <button onClick={_event => self.send(NextSlide)} style={rightControlStyle(isDarkMode)}></button>
      </aside>
    </div>;
  },
};
