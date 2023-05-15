# Nutritional-Facts
Nutritional Facts is a program that displays a list of the highest or lowest values of a specific macronutrient via the user.
Problem: 
	People are unaware of the suitable intake of different vitamins and minerals in foods. This can be challenging for some individuals with certain dietary restrictions or health concerns. Being unaware can lead to imbalances or deficiencies that can affect the body negatively. For example, if one does not reach a high level of iron, it can turn into anemia and result in fatigue.
 	They may also not know which minerals or vitamins they should have more or less of. Another example could be someone with high blood pressure who may have to limit their intake of sodium to ensure better control over their condition. We want to suggest food options that will help people, including those with high blood pressure, make better food choices to maintain optimal health. In our program, we based the output on what the user is asking for, whether they want to increase or decrease their intake of a specific macronutrient. We would provide the minimum or maximum suitable amount to help users make knowledgeable decisions for their diet.


Motivation: 
	This is a problem because people may not know what nutrients are within the food or drinks they are intaking. The user may not be well-educated about what the food labels say or fall for misleading marketing. Someone may not know that a particular food item is high in sugar and without knowing this, they are unable to make optimal choices for their diet.
People may also not know where to look when they want to eat more of a specific macronutrient. Our program can offer suggestions of foods that contain a high or low number of macronutrient-based on what the user is looking for. We can provide easy access to food information. Further preventing our users from being uninformed, and avoiding serious health problems such as obesity, heart problems, and diabetes.


Features:
We know we have solved the problem when we know that the user receives the information they asked for based on the inputs they provided. The user can decide what category of food/drink they want the highest or lowest value for, and which macronutrient they want more information on. For example, if the user wants to see what kind of foods have low sodium, we provide food options and categories that have low sodium. The same idea follows if the user wants to see a list of items in a category with the highest protein value.


Description of data: 
	The dataset we are using comes from the United States Department of Agriculture’s Food Composition Database. It contains a variety of food and drink types with associated different vitamins and minerals found in each type (macronutrient percentages). The macronutrients we are utilizing from the data set include: category, description, cholesterol, sodium, protein, fiber, sugar, and carbohydrates. This is the link to the set: https://think.cs.vt.edu/corgis/csv/food/ .

Tools/Language/APIs/Libraries used:
	C++, Priority Queue, ChatGPT

Algorithm implemented:
	The scope of our project was minimized and doing so, allowed us to use a library for a priority queue. We created a k-largest element and k-smallest element function with the heap to put all of the items in their desired location for the sorting algorithm. We also created a Tim Sort, which utilizes both an insertion and merge sort to work properly to sort the items into their final destination to later be printed to the user.
