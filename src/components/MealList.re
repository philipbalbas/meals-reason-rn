open ReactNative;
open ReactNavigation;
open Models;

let styles =
  Style.(
    StyleSheet.create({
      "list":
        style(
          ~flex=1.,
          ~justifyContent=`center,
          ~alignItems=`center,
          ~padding=15.->dp,
          (),
        ),
    })
  );

[@react.component]
let make = (~listData, ~navigation) => {
  let renderMealItem =
      (itemData: ReactNative.VirtualizedList.renderItemProps(meal)) => {
    <MealItem
      item={
        itemData##item;
      }
      onSelectMeal={_ =>
        navigation->Navigation.navigateWithParams(
          "MealDetail",
          {"mealId": itemData##item.id},
        )
      }
    />;
  };

  <View style=styles##list>
    <FlatList
      data=listData
      keyExtractor={(item, _index) => item.id}
      renderItem=renderMealItem
      style=Style.(style(~width=100.->pct, ()))
    />
  </View>;
};