open ReactNative;
open ReactNavigation;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
    })
  );

[@react.component]
let make = (~navigation) => {
  let favMeals =
    DummyData.meals
    ->Belt.Map.String.valuesToArray
    ->Belt.Array.keep(m => m.id == "m1" || m.id == "m2");

  <MealList listData=favMeals navigation />;
};

make->NavigationOptions.setDynamicNavigationOptions(navData => {
  Js.log(navData);
  NavigationOptions.t(
    ~title="Your Favorites",
    ~headerLeft=
      <Button
        title="Open"
        onPress={_ => navData##navigation->Navigation.toggleDrawer}
      />,
    (),
  );
});