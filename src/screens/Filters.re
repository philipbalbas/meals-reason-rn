open ReactNative;
open ReactNavigation;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen": style(~flex=1., ~alignItems=`center, ()),
      "title":
        style(
          ~fontFamily="open-sans-bold",
          ~fontSize=22.,
          ~margin=20.->dp,
          ~textAlign=`center,
          (),
        ),
      "filterContainer":
        style(
          ~flexDirection=`row,
          ~justifyContent=`spaceBetween,
          ~alignItems=`center,
          ~width=80.->pct,
          ~marginVertical=15.->dp,
          (),
        ),
    })
  );

module FilterSwitch = {
  [@react.component]
  let make = (~label, ~state, ~onChange) =>
    <View style=styles##filterContainer>
      <Text> label->str </Text>
      <Switch
        trackColor={Switch.trackColor(
          ~_true=Constants.Colors.primaryColor,
          (),
        )}
        thumbColor={
          Platform.os == Platform.android ? Constants.Colors.primaryColor : ""
        }
        onValueChange=onChange
        value=state
      />
    </View>;
};

[@react.component]
let make = (~navigation) => {
  let (isGlutenFree, setIsGlutenFree) = React.useState(() => false);
  let (isLactoseFree, setIsLactoseFree) = React.useState(() => false);
  let (isVegan, setIsVegan) = React.useState(() => false);
  let (isVegetarian, setIsVegetarian) = React.useState(() => false);

  let savedFilters =
    React.useCallback(() => {
      let appliedFileters = {
        "isGlutenFree": isGlutenFree,
        "isLactoseFree": isLactoseFree,
        "isVegan": isVegan,
        "isVegetarian": isVegetarian,
      };

      appliedFileters;
    });

  React.useEffect1(
    () => {
      navigation->NavUtils.setParams({"save": savedFilters});
      None;
    },
    [|isGlutenFree|],
  );

  <View style=styles##screen>
    <Text style=styles##title> "Available Filters / Restrictions"->str </Text>
    <FilterSwitch
      label="Gluten-free"
      state=isGlutenFree
      onChange={value => setIsGlutenFree(_ => value)}
    />
    <FilterSwitch
      label="Lactose-free"
      state=isLactoseFree
      onChange={value => setIsLactoseFree(_ => value)}
    />
    <FilterSwitch
      label="Vegan"
      state=isVegan
      onChange={value => setIsVegan(_ => value)}
    />
    <FilterSwitch
      label="Vegetarian"
      state=isVegetarian
      onChange={value => setIsVegetarian(_ => value)}
    />
  </View>;
};

make->NavigationOptions.setDynamicNavigationOptions(navData =>
  NavigationOptions.t(
    ~title="Filter",
    ~headerLeft=
      <Button
        title="Open"
        onPress={_ => navData##navigation->Navigation.toggleDrawer}
      />,
    (),
  )
);