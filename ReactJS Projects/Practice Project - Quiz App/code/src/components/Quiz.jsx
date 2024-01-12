import { useState, useContext, useCallback } from 'react';
import { AnswerContext } from '../store/answer-context.jsx';
import Answers from './Answers.jsx';
import Summary from './Summary.jsx';
import ProgressBar from './ProgressBar.jsx';
import { QUESTION } from '../questions.js';

export default function Quiz({ }) {
    const [activeQuestionIndex, setActiveQuestionIndex] = useState(1);
    const [questionState, setQuestionState] = useState('unanswered');
    const quizIsComplete = activeQuestionIndex === QUESTION.length + 1;
    let timer = 10000;
    let classes = '';

    const { selected, selectedAnswers, selectItem, checkAnswers, checkItem, skipItem } = useContext(AnswerContext);

    if (questionState === 'selected') {
        timer = 1000;
        classes = questionState;
    }

    if (questionState === 'check') {
        timer = 2000;
        classes = checkAnswers[activeQuestionIndex - 1];
    }

    if (questionState === 'skip') {
        timer += (Math.random() * 10);       
    }
  

    const handleOnTimeout = useCallback(function handleOnTimeout() {
        skipItem();
        setQuestionState('skip');
        setActiveQuestionIndex((prevstate) => prevstate + 1);
    }, [selectItem]);

    function handleSelectAnswer(answer) {
        selectItem(answer);
        setQuestionState('selected');

        setTimeout(() => {
            checkItem();
            setQuestionState('check');

            setTimeout(() => {
                setActiveQuestionIndex((prevstate) => prevstate + 1);
                setQuestionState('unanswered');  
            }, 2000);
        }, 1000);
    }

    const currentQuestion = QUESTION.find(question => {
        return question.id === `q${activeQuestionIndex}`;
    });
 
    return (
        <>
            {!quizIsComplete ? (
                <section id="quiz" >
                    <div id="question">
                        <ProgressBar key={timer} timer={timer} onTimeout={(questionState === 'unanswered' || questionState === 'skip')? handleOnTimeout : null} mode={classes}/>
                        <h2>{currentQuestion.text}</h2>
                        <Answers key={activeQuestionIndex} newClass={classes} activeIndex={activeQuestionIndex} selectedAnswers={selectedAnswers} onSelect={handleSelectAnswer} />
                    </div>
                </section>
            ) : (
                <Summary />
            )}
        </>
    );
}
