import logoImg from './assets/quiz-logo.png';
import Quiz from './components/Quiz.jsx';
import AnswerContextProvider from './store/answer-context.jsx';

function App() {
    return (
        <AnswerContextProvider>
            <header>
                <img src={logoImg} alt="Quiz" />
                <h1>ReactQuiz</h1>
            </header>
            <main>
                <Quiz />
            </main>
        </AnswerContextProvider>
    );
}
    
export default App;
