[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  switch url.path {
  | ["posts"] => <PostsPage />
  | _ => {
      ReasonReactRouter.replace("/posts");
      ReasonReact.null;
    }
  };
};
