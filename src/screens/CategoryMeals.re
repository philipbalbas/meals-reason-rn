open ReactNative;
open ReactNavigation;
open Models;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
    })
  );

let getCategory = (navigation, p) => {
  navigation
  ->Navigation.getParam(p)
  ->Js.Nullable.toOption
  ->Belt.Option.flatMap(catId =>
      DummyData.categories->Belt.Map.String.get(catId)
    );
};

[@react.component]
let make = (~navigation) => {
  let category = navigation->getCategory("categoryId");
  let displayedMeals =
    switch (category) {
    | None => [||]
    | Some(c) =>
      DummyData.meals
      ->Belt.Map.String.valuesToArray
      ->Belt.Array.keep(m =>
          m.categoryIds->Belt.Array.some(cat => cat == c.id)
        )
    };

  <MealList listData=displayedMeals navigation />;
};

make->NavigationOptions.setDynamicNavigationOptions(params =>
  NavigationOptions.t(
    ~title=
      params##navigation
      ->getCategory("categoryId")
      ->Belt.Option.mapWithDefault("Missing", v => v.title),
    (),
  )
);