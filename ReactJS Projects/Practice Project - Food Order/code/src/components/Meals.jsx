import { currencyFormatter } from '../util/formatting.js';
import { useContext } from 'react';
import { CartContext } from '../store/order-cart-context.jsx';

export default function Meals({ data, isLoading, error }) {
    const { addItemToCart } = useContext(CartContext);

    if (error) {
        return (
            <div className="error">
                <h2>Error</h2>
                <p >{error.message}</p>
            </div>
        );
    }

    return (
        <section>
            {isLoading && <p className="center">Fetching meals data...</p>}
            {!isLoading && data.length === 0 && <p className="center">No meals available.</p>}
            {!isLoading && data.length > 0 && (
                <ul id="meals">
                    {data.map((meal) => {
                        //console.log(meal.name);
                        return (
                            <li key={meal.id} className="meal-item">
                                <article>
                                    <img
                                        src={`https://practice-project-food-order.onrender.com/${meal.image}`}
                                        alt={meal.name}
                                    />
                                    <div>
                                        <h3>{meal.name}</h3>
                                        <p className="meal-item-price">{currencyFormatter.format(meal.price)}</p>
                                        <p className="meal-item-description">{meal.description}</p>
                                    </div>
                                    <p>
                                        <button className="meal-item-actions text-button" onClick={() => addItemToCart(meal)}>Add to Cart</button>
                                    </p>
                                </article>
                            </li>
                        )
                    })}
                </ul>
            )}
        </section>
    );
}