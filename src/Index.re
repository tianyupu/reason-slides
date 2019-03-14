let content = [
  ["# Slide 1", "Subcontent 1"],
  ["# Slide 2"],
  ["# Slide 3", "_Subcontent_ 1", "**Subcontent** 2", "## Subcontent 3", "Subcontent 4"],
];

// Js.Promise.(
//   Fetch.fetch("/slide-content.md")
//   |> then_(Fetch.Response.text)
//   |> then_(text => Str.split(regexp("---"), text))
//   |> then_(text => print_endline(List.nth(0, text)))
//   |> resolve)
// );

ReactDOMRe.renderToElementWithId(<Slides content={content}/>, "index1");