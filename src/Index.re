let slideSeparator = "\n---\n";
let slideContentSeparator = "\n\n";
let fixedSlideIndicator = "\n";

Js.Promise.(
  Fetch.fetch("slide-content.md")
  |> then_(Fetch.Response.text)
  |> then_(text => Array.to_list(Js.String.split(slideSeparator, text)) |> resolve)
  |> then_(slideArray => 
    List.map(slide => Js.String.startsWith(fixedSlideIndicator, slide) ?
                        [slide] :
                        Array.to_list(Js.String.split(slideContentSeparator, slide)), slideArray) 
    |> resolve)
  |> then_(slideContent =>
    ReactDOMRe.renderToElementWithId(<Slides content={slideContent} />, "index")
    |> resolve)
);