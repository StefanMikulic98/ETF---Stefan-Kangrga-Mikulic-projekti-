export async function fetchMeals() {
    const response = await fetch('https://practice-project-food-order.onrender.com/meals');
    const resData = await response.json();

    if (!response.ok) {
        throw new Error('Failed to fetch places');
    }

    return resData;
}

