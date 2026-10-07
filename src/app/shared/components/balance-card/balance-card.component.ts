import {
  ChangeDetectionStrategy,
  Component,
  Input,
} from '@angular/core';

import { CurrencyPipe } from '@angular/common';

@Component({
  selector: 'app-balance-card',
  standalone: true,
  imports: [CurrencyPipe],
  templateUrl: './balance-card.component.html',
  styleUrl: './balance-card.component.scss',
  changeDetection: ChangeDetectionStrategy.OnPush,
})
export class BalanceCardComponent {
  @Input() totalBalance = 0;
  @Input() maskedAccount = '';
  @Input() balanceTrendPercentage = 0;
}
