import Header from './components/Header';
import Meals from './components/Meals';
import { useFetch } from './hooks/useFetch.js';
import { fetchMeals } from './http.js';
import CartContextProvider from './store/order-cart-context.jsx';


function App() {

    const {
        isFetching,
        error,
        fetchedData: meals,
    } = useFetch(fetchMeals, []);   

    return (
        <CartContextProvider>
            <Header />
            <Meals isLoading={isFetching} error={error} data={meals} />
        </CartContextProvider>
    );
}

export default App;
