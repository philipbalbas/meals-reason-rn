open ReactNative;
open ReactNavigation;
open Models;

let str = React.string;

let styles =
  Style.(
    StyleSheet.create({
      "screen":
        style(~flex=1., ~justifyContent=`center, ~alignItems=`center, ()),
      "header": style(~backgroundColor=Constants.Colors.primaryColor),
    })
  );

[@react.component]
let make = (~navigation) => {
  let renderGridItem =
      (itemData: ReactNative.VirtualizedList.renderItemProps(category)) => {
    <CategoryGridTile
      title={itemData##item.title}
      color={itemData##item.color}
      onSelect={_ =>
        navigation->Navigation.navigateWithParams(
          "CategoryMeals",
          {"categoryId": itemData##item.id},
        )
      }
    />;
  };

let data = DummyData.categories->Belt.Map.String.valuesToArray;

  <FlatList
    numColumns=2
    data={DummyData.categories->Belt.Map.String.valuesToArray}
    renderItem=renderGridItem
    keyExtractor={(item, _) => item.id}
  />;
};

let bgColor =
  Platform.os == Platform.android ? Constants.Colors.primaryColor : "#fff";

let headerColor =
  Platform.os == Platform.android ? "#fff" : Constants.Colors.primaryColor;

make->NavigationOptions.setDynamicNavigationOptions(navData =>
  NavigationOptions.t(
    ~title="Meal Categories",
    ~headerStyle={
      Style.style(~backgroundColor=bgColor, ());
    },
    ~headerTintColor=headerColor,
    ~headerLeft=
      <Button
        title="Open"
        onPress={_ => navData##navigation->Navigation.toggleDrawer}
      />,
    (),
  )
);