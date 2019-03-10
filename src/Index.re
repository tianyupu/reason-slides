// ReactDOMRe.renderToElementWithId(<Component1 message="Hello! Click this text." />, "index1");

// ReactDOMRe.renderToElementWithId(<Component2 greeting="Hello!" />, "index2");

let content = [
  ["Slide 1 Subcontent 1", "Slide 1 Subcontent 2"],
  ["Slide 2 Subconten 1"],
  ["Slide 3 Subcontent 1", "Slide 3 Subcontent 2", "Slide 3 Subcontent 3", "Slide 3 Subcontent 4"],
]

ReactDOMRe.renderToElementWithId(<Slides content={content}/>, "index1");