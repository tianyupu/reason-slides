// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");
var Slide$ReactTemplate = require("./Slide.bs.js");

var component = ReasonReact.reducerComponent("Slides");

var style = {
  backgroundColor: "#eba6f4",
  height: "100%",
  overflow: "hidden",
  position: "relative",
  width: "100%"
};

var controlsStyle = {
  bottom: "20px",
  position: "fixed",
  right: "10px"
};

var leftControlStyle = {
  backgroundColor: "transparent",
  border: "12px solid transparent",
  borderRightColor: "#777",
  borderRightWidth: "22px",
  cursor: "pointer",
  margin: "0 5px 0 5px",
  padding: "0"
};

var rightControlStyle = {
  backgroundColor: "transparent",
  border: "12px solid transparent",
  borderLeftColor: "#777",
  borderLeftWidth: "22px",
  cursor: "pointer",
  margin: "0 5px 0 5px",
  padding: "0"
};

function make(content, isLoading, _children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              self[/* state */1][/* keyDownHandler */2][0] = (function (e) {
                  var match = e.key;
                  switch (match) {
                    case "ArrowLeft" : 
                        return Curry._1(self[/* send */3], /* PreviousSlide */0);
                    case "ArrowRight" : 
                        return Curry._1(self[/* send */3], /* NextSlide */1);
                    default:
                      return /* () */0;
                  }
                });
              document.addEventListener("keydown", self[/* state */1][/* keyDownHandler */2][0]);
              return /* () */0;
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */(function (self) {
              document.removeEventListener("keydown", self[/* state */1][/* keyDownHandler */2][0]);
              return /* () */0;
            }),
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var slideContents = List.nth(content, self[/* state */1][/* currentSlide */0]);
              if (isLoading) {
                return React.createElement("h1", undefined, "Loading slides...");
              } else {
                return React.createElement("div", {
                            style: style
                          }, ReasonReact.element(undefined, undefined, Slide$ReactTemplate.make(slideContents, self[/* state */1][/* currentSlideContent */1], /* array */[])), React.createElement("aside", {
                                style: controlsStyle
                              }, React.createElement("button", {
                                    style: leftControlStyle,
                                    onClick: (function (_event) {
                                        return Curry._1(self[/* send */3], /* PreviousSlide */0);
                                      })
                                  }), React.createElement("button", {
                                    style: rightControlStyle,
                                    onClick: (function (_event) {
                                        return Curry._1(self[/* send */3], /* NextSlide */1);
                                      })
                                  })));
              }
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* currentSlide */0,
                      /* currentSlideContent */0,
                      /* keyDownHandler : record */[/* contents */(function (_e) {
                            return /* () */0;
                          })]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action) {
                var lastContentOnThisSlide = List.length(List.nth(content, state[/* currentSlide */0])) - 1 | 0;
                var lastSlide = List.length(content) - 1 | 0;
                var match = state[/* currentSlideContent */1] >= lastContentOnThisSlide;
                var match$1 = state[/* currentSlide */0] === lastSlide && state[/* currentSlideContent */1] === lastContentOnThisSlide;
                var tmp;
                if (match$1) {
                  tmp = state[/* currentSlideContent */1];
                } else {
                  var match$2 = state[/* currentSlideContent */1] >= lastContentOnThisSlide;
                  tmp = Caml_primitive.caml_int_min(match$2 ? 0 : state[/* currentSlideContent */1] + 1 | 0, lastContentOnThisSlide);
                }
                return /* Update */Block.__(0, [/* record */[
                            /* currentSlide */Caml_primitive.caml_int_min(match ? state[/* currentSlide */0] + 1 | 0 : state[/* currentSlide */0], lastSlide),
                            /* currentSlideContent */tmp,
                            /* keyDownHandler */state[/* keyDownHandler */2]
                          ]]);
              } else {
                var match$3 = state[/* currentSlide */0] > 0;
                var lastContentOnPreviousSlide = match$3 ? List.length(List.nth(content, state[/* currentSlide */0] - 1 | 0)) - 1 | 0 : -1;
                var match$4 = state[/* currentSlideContent */1] <= 0;
                var match$5 = state[/* currentSlideContent */1] <= 0 && state[/* currentSlide */0] <= 0;
                var tmp$1;
                if (match$5) {
                  tmp$1 = 0;
                } else {
                  var match$6 = state[/* currentSlideContent */1] <= 0;
                  tmp$1 = Caml_primitive.caml_int_max(match$6 ? lastContentOnPreviousSlide : state[/* currentSlideContent */1] - 1 | 0, 0);
                }
                return /* Update */Block.__(0, [/* record */[
                            /* currentSlide */Caml_primitive.caml_int_max(match$4 ? state[/* currentSlide */0] - 1 | 0 : state[/* currentSlide */0], 0),
                            /* currentSlideContent */tmp$1,
                            /* keyDownHandler */state[/* keyDownHandler */2]
                          ]]);
              }
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.component = component;
exports.style = style;
exports.controlsStyle = controlsStyle;
exports.leftControlStyle = leftControlStyle;
exports.rightControlStyle = rightControlStyle;
exports.make = make;
/* component Not a pure module */
