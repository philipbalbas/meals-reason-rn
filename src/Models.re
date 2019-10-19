[@bs.deriving jsConverter]
type affordability = [ | `affordable | `pricey | `luxurious];

[@bs.deriving jsConverter]
type complexity = [ | `simple | `hard | `challenging];

type category = {
  id: string,
  title: string,
  color: string,
};

type meal = {
  id: string,
  title: string,
  categoryIds: array(string),
  affordability,
  complexity,
  imageUrl: string,
  duration: int,
  ingredients: array(string),
  steps: array(string),
  isGlutenFree: bool,
  isVegan: bool,
  isVegetarian: bool,
  isLactoseFree: bool,
};