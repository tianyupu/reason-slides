let slideSeparator = "\n---\n";
let slideContentSeparator = "\n\n";

ReactDOMRe.renderToElementWithId(<Slides isLoading={true} content={[[]]} />, "index1");

Js.Promise.(
  Fetch.fetch("slide-content.md")
  |> then_(Fetch.Response.text)
  |> then_(text => Array.to_list(Js.String.split(slideSeparator, text)) |> resolve)
  |> then_(slideArray => List.map(slide => Array.to_list(Js.String.split(slideContentSeparator, slide)), slideArray) |> resolve)
  |> then_(slideContent => ReactDOMRe.renderToElementWithId(<Slides isLoading={false} content={slideContent} />, "index1") |> resolve)
);