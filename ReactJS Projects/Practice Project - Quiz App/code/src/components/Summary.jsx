import endLogo from '../assets/quiz-complete.png';
import { useContext } from 'react';
import { AnswerContext } from '../store/answer-context.jsx';
import { QUESTION as QUESTIONS } from '../questions.js';


export default function Summary() {
    const { checkAnswers, selectedAnswers } = useContext(AnswerContext);

    let correctAnswers = (((checkAnswers.filter(answer => answer === 'correct')).length / checkAnswers.length) * 100).toFixed(0);
    let wrongAnswers = (((checkAnswers.filter(answer => answer === 'wrong')).length / checkAnswers.length) * 100).toFixed(0);
    let skippedAnswers = (((checkAnswers.filter(answer => answer === 'skip')).length / checkAnswers.length) * 100).toFixed(0);

    return (
        <div id="summary">
            <img src={endLogo} alt="Trophy icon" />
            <h2>Quiz Completed!</h2>
            <div id="summary-stats">

                <p>
                    <span className="number">{skippedAnswers}%</span>
                    <span className="text">skipped</span>
                </p>
                <p>
                    <span className="number">{correctAnswers}%</span>
                    <span className="text">answered correctly</span>
                </p>
                <p>
                    <span className="number">{wrongAnswers}%</span>
                    <span className="text">answered incorrectly</span>
                </p>              
            </div>

            <ol>
                {selectedAnswers.map((answer, index) => {
                    let cssClass = 'user-answer';

                    if (answer === '') {
                        cssClass += ' skipped';
                    } else if (answer === QUESTIONS[index].answers[0]) {
                        cssClass += ' correct';
                    } else {
                        cssClass += ' wrong';
                    }
                    console.log(index + ' : ' + cssClass)
                    return (
                        <li key={index}>
                            <p className="question">
                                {QUESTIONS[index].text}
                            </p>
                            <div className="user-answer">
                                <p className={cssClass}>
                                    {answer !== '' ? answer : 'Skipped'}
                                </p>
                            </div>
                        </li>
                    )
                })}
            </ol>
        </div>
    );
}