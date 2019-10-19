open ReactNavigation;
open ReactNative;

let styles =
  Style.(
    style(
      ~backgroundColor=
        Platform.os == Platform.android
          ? Constants.Colors.primaryColor : "white",
      (),
    )
  );

let tabBarIcon = (~icon) => {
  NavigationOptions.TabBarIcon.render(tabInfo =>
    <Icons.Ionicons name=icon size=25. color=tabInfo##tintColor />
  );
};

let defaultNavigationOptions = {
  "headerTintColor":
    Platform.os == Platform.android ? "#fff" : Constants.Colors.primaryColor,
  "headerStyle":
    Style.(
      style(
        ~backgroundColor={
          Platform.os == Platform.android ? Constants.Colors.primaryColor : "";
        },
        (),
      )
    ),
  "headerTitleStyle": Style.(style(~fontFamily="open-sans-bold", ())),
  "headerBackTitleStyle": Style.(style(~fontFamily="open-sans"), ()),
};

module MealsNavigator = {
  let config = StackUtils.config(~defaultNavigationOptions, ());

  type screenProps = unit;

  let navigator =
    StackNavigator.makeWithConfig(
      {
        "Categories": {
          screen: Categories.make,
        },
        "CategoryMeals": {
          screen: CategoryMeals.make,
        },
        "MealDetail": {
          screen: MealDetail.make,
        },
      },
      config,
    );
};

module FavNavigator = {
  let config = StackUtils.config(~defaultNavigationOptions, ());

  let navigator =
    StackNavigator.makeWithConfig(
      {"Favorites": Favorite.make, "MealDetail": MealDetail.make},
      config,
    );
};

module MealsFavTabNavigator = {
  let navigator =
    TabNavigator.(
      Bottom.makeWithConfig(
        {
          "Meals": {
            screen: MealsNavigator.navigator,
            navigationOption:
              MealsNavigator.navigator->NavigationOptions.setNavigationOptions(
                NavigationOptions.t(
                  ~title="Meat",
                  ~tabBarIcon=tabBarIcon("ios-restaurant"),
                  (),
                ),
              ),
          },
          "Favorites": {
            screen: FavNavigator.navigator,
            navigationOption:
              FavNavigator.navigator->NavigationOptions.setNavigationOptions(
                NavigationOptions.t(
                  ~title="Favorite",
                  ~tabBarIcon=tabBarIcon("ios-star"),
                  (),
                ),
              ),
          },
        },
        config(
          ~tabBarOptions=
            tabBarOptions(~activeTintColor=Constants.Colors.accentColor, ()),
          (),
        ),
      )
    );
};

module FiltersNavigator = {
  let config = StackUtils.config(~defaultNavigationOptions, ());

  let navigator =
    StackNavigator.makeWithConfig({"Filters": Filters.make}, config);
};

module MainNavigator =
  AppContainer.Make({
    type screenProps = unit;

    let navigator =
      DrawerNavigator.(
        makeWithConfig(
          {
            "MealsFavs": {
              screen: MealsFavTabNavigator.navigator,
              navigationOption:
                MealsFavTabNavigator.navigator->NavigationOptions.setNavigationOptions(
                  NavigationOptions.t(~title="Meals", ()),
                ),
            },
            "Filters": FiltersNavigator.navigator,
          },
          config(
            ~contentOptions={
              contentOptions(
                ~activeTintColor="#bbb",
                ~labelStyle={
                  Style.(style(~fontFamily="open-sans-bold", ()));
                },
                (),
              );
            },
            (),
          ),
        )
      );
  });

[@react.component]
let make = () => {
  <MainNavigator />;
};