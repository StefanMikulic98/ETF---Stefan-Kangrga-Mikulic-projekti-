import { useState, useEffect, useContext } from 'react';
import { AnswerContext } from '../store/answer-context.jsx';

let TIMER = 7000;

export default function Question({questionText}) {
    const [remainingTime, setRemainingTime] = useState(TIMER);

    const { selected } = useContext(AnswerContext);

    if (selected) {
        TIMER = 2000;
    }


    useEffect(() => {
        const interval = setInterval(() => {
            console.log('Set Timer');
            setRemainingTime((prevTime) => prevTime - 10);
        }, 10);

        return () => {
            console.log('Clear Timer');
            clearInterval(interval);
        };
    }, [TIMER]);

    return (
        <div id="question">
            <progress value={remainingTime} max={TIMER} />
            <h2>{questionText}</h2>               
        </div>      
    );
}
