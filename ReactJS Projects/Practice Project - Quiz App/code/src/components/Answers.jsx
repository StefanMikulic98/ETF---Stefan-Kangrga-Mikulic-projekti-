import { useRef } from 'react';
import { QUESTION } from '../questions.js';

export default function Answers({ newClass, activeIndex, selectedAnswers, onSelect }) {
    const shuffledAnswers = useRef();

    if (!shuffledAnswers.current) {
        shuffledAnswers.current = [...QUESTION[activeIndex - 1].answers];
        shuffledAnswers.current.sort(() => Math.random() - 0.5);
    }

    return (
        <ul id="answers">
            {shuffledAnswers.current.map((answer) => {
                let cssClass = '';
                if (selectedAnswers[selectedAnswers.length-1] === answer) {
                    cssClass = newClass;
                }                
                return (
                    <li key={answer} className="answer">
                        <div className="answer">                          
                            <button
                                className={cssClass}
                                onClick={() => onSelect(answer)}
                                disabled={newClass !== ''}
                            >
                                {answer}
                            </button>
                        </div>
                    </li>
                )
            })}
        </ul>


    );
}